#include "Player.h"

#include <iostream>

#define NOMINMAX

#include <Windows.h>

#include "GameHeader.h"
#include "Input.h"

Player::Player()
{
  Player::Reset();
  hitSpheres.push_back(Sphere(Vector3(0, 0, 0), GH::PLAYER_RADIUS));
  hitSpheres.push_back(Sphere(Vector3(0, GH::PLAYER_RADIUS - GH::PLAYER_HEIGHT, 0), GH::PLAYER_RADIUS));
}

void Player::Reset()
{
  Physical::Reset();
  cam_rx = 0.0f;
  cam_ry = 0.0f;
  bob_mag = 0.0f;
  bob_phi = 0.0f;
  friction = 0.04f;
  drag = 0.002f;
  onGround = true;
}

void Player::Update()
{
  // Update bobbing motion
  float magT = (prev_pos - pos).Mag() / (GH::DT * p_scale);
  if(!onGround)
  {
    magT = 0.0f;
  }
  bob_mag = bob_mag * (1.0f - GH::BOB_DAMP) + magT * GH::BOB_DAMP;
  if(bob_mag < GH::BOB_MIN)
  {
    bob_phi = 0.0f;
  }
  else
  {
    bob_phi += GH::BOB_FREQ * GH::DT;
    if(bob_phi > 2 * GH::PI)
    {
      bob_phi -= 2 * GH::PI;
    }
  }

  // Physics
  Physical::Update();

  // Looking
  Look(GH::INPUT->mouse_dx, GH::INPUT->mouse_dy);

  // Movement
  float moveF = 0.0f;
  float moveL = 0.0f;
  if(GH::INPUT->key['W'])
  {
    moveF += 1.0f;
  }
  if(GH::INPUT->key['S'])
  {
    moveF -= 1.0f;
  }
  if(GH::INPUT->key['A'])
  {
    moveL += 1.0f;
  }
  if(GH::INPUT->key['D'])
  {
    moveL -= 1.0f;
  }
  Move(moveF, moveL);

#if 0
  //Jumping
  if (onGround && GH::INPUT->key[VK_SPACE]) {
    velocity.y += 2.0f * p_scale;
  }
#endif

  // Reset ground state after update finishes
  onGround = false;
}

void Player::Look(float mouseDx, float mouseDy)
{
  // Adjust x-axis rotation
  cam_rx -= mouseDy * GH::MOUSE_SENSITIVITY;
  if(cam_rx > GH::PI / 2)
  {
    cam_rx = GH::PI / 2;
  }
  else if(cam_rx < -GH::PI / 2)
  {
    cam_rx = -GH::PI / 2;
  }

  // Adjust y-axis rotation
  cam_ry -= mouseDx * GH::MOUSE_SENSITIVITY;
  if(cam_ry > GH::PI)
  {
    cam_ry -= GH::PI * 2;
  }
  else if(cam_ry < -GH::PI)
  {
    cam_ry += GH::PI * 2;
  }
}

void Player::Move(float moveF, float moveL)
{
  // Make sure movement is not too fast
  const float mag = std::sqrt(moveF * moveF + moveL * moveL);
  if(mag > 1.0f)
  {
    moveF /= mag;
    moveL /= mag;
  }

  // Movement
  const Matrix4 camToWorld = LocalToWorld() * Matrix4::RotY(cam_ry);
  velocity += camToWorld.MulDirection(Vector3(-moveL, 0, -moveF)) * (GH::WALK_ACCEL * GH::DT);

  // Don't allow non-falling speeds above the player's max speed
  const float tempY = velocity.y;
  velocity.y = 0.0f;
  velocity.ClipMag(p_scale * GH::WALK_SPEED);
  velocity.y = tempY;
}

void Player::OnCollide(Object& other, const Vector3& push)
{
  // Prevent player from rolling down hills if they're not too steep
  Vector3 newPush = push;
  if(push.Normalized().y > 0.7f)
  {
    newPush.x = 0.0f;
    newPush.z = 0.0f;
    onGround = true;
  }

  // Friction should only apply when player is on ground
  const float cur_friction = friction;
  if(!onGround)
  {
    friction = 0.0f;
  }

  // Base call
  Physical::OnCollide(other, newPush);
  friction = cur_friction;
}

Matrix4 Player::WorldToCam() const
{
  return Matrix4::RotX(-cam_rx) * Matrix4::RotY(-cam_ry) * Matrix4::Trans(-CamOffset()) * WorldToLocal();
}

Matrix4 Player::CamToWorld() const
{
  return LocalToWorld() * Matrix4::Trans(CamOffset()) * Matrix4::RotY(cam_ry) * Matrix4::RotX(cam_rx);
}

Vector3 Player::CamOffset() const
{
  // If bob is too small, don't even bother
  if(bob_mag < GH::BOB_MIN)
  {
    return Vector3::Zero();
  }

  // Convert bob to translation
  const float theta = (GH::PI / 2) * std::sin(bob_phi);
  const float y = bob_mag * GH::BOB_OFFS * (1.0f - std::cos(theta));
  return Vector3(0, y, 0);
}
