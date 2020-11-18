#include "Model.hpp"

Model::Model(telemetry::Items& telemetryItems) {
  telemetry::ItemString* parts = new telemetry::ItemString(telemetry::ROOT_ITEM_ID, "Parts", "2");
  telemetryItems.add_item(parts);

  telemetry::ItemSTL* left_foot = new telemetry::ItemSTL(parts->getId(),
    "Left foot", "../model/suction-cup-connector.stl",
    { { TRANSFORM_TYPE_MOVE, 0, -75 } });
  telemetryItems.add_item(left_foot);

  telemetry::ItemSTL* right_foot = new telemetry::ItemSTL(parts->getId(),
    "Right foot", "../model/suction-cup-connector.stl",
    { { TRANSFORM_TYPE_MOVE, 0, 75 } });
  telemetryItems.add_item(right_foot);
}

void Model::reset() {
  // TODO: implement
}