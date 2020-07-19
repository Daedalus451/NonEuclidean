#pragma once

#include "Physical.h"
#include "Vector.h"

class Player : public Physical
{
public:
  Player();
  ~Player() override = default;

  void Reset() override;
  void Update() override;
  void OnCollide(Object& other, const Vector3& push) override;

  void Look(float mouseDx, float mouseDy);
  void Move(float moveF, float moveL);

  Matrix4 WorldToCam() const;
  Matrix4 CamToWorld() const;
  Vector3 CamOffset() const;

private:
  float cam_rx = 0.0f;
  float cam_ry = 0.0f;

  float bob_mag = 0.0f;
  float bob_phi = 0.0f;

  bool onGround = true;
};
