#pragma once

#include "Object.h"
#include "Portal.h"
#include "Sphere.h"

class Physical : public Object
{
public:
  Physical();

  ~Physical() override = default;

  void Reset() override;
  void Update() override;
  virtual void OnCollide(Object& other, const Vector3& push);

  void SetPosition(const Vector3& _pos)
  {
    pos = _pos;
    prev_pos = _pos;
  }

  bool TryPortal(const Portal& portal);

  Physical* AsPhysical() override
  {
    return this;
  }

  Vector3 gravity;
  Vector3 velocity;
  float bounce = 0.0f;
  float friction = 0.0f;
  float high_friction = 0.0f;
  float drag = 0.0f;

  Vector3 prev_pos;

  std::vector<Sphere> hitSpheres;
};
