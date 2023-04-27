#include "PathStrategy.h"

PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {}

void PathStrategy::Move(IEntity* entity, double dt) {
  if (IsCompleted())
    return;

  Vector3 vi(path[index][0], path[index][1], path[index][2]);
  Vector3 dir = (vi - entity->GetPosition()).Unit();

  entity->SetPosition(entity->GetPosition() + dir*entity->GetSpeed()*dt);
  entity->SetDirection(dir);

  if (entity->GetPosition().Distance(vi) < 4)
    index++;
}

bool PathStrategy::IsCompleted() {
  return index >= path.size();
}

double PathStrategy::GetDistance(Vector3 from) {
  Vector3 vectorFromPoint = from;
  vectorFromPoint.x -= path.at(index).at(0);
  vectorFromPoint.y -= path.at(index).at(1);
  vectorFromPoint.z -= path.at(index).at(2);
  double result = vectorFromPoint.Magnitude();

  for (int i = index + 1; i < path.size(); i++) {
    Vector3 betweenPath(path.at(i).at(0), path.at(i).at(1), path.at(i).at(2));
    betweenPath.x -= path.at(i - 1).at(0);
    betweenPath.y -= path.at(i - 1).at(1);
    betweenPath.z -= path.at(i - 1).at(2);
    result += betweenPath.Magnitude();
  }
}
