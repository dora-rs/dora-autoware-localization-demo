/*
 *  Copyright(c) 2021 to 2023 AutoCore Technology (Nanjing) Co., Ltd. All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 */

// Copyright 2020 Tier IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TIER4_AUTOWARE_UTILS__ROS__MARKER_HELPER_HPP_
#define TIER4_AUTOWARE_UTILS__ROS__MARKER_HELPER_HPP_

#include <rclcpp/rclcpp.hpp>

#include <visualization_msgs/msg/marker_array.hpp>

#include <boost/optional.hpp>

#include <string>

namespace tier4_autoware_utils
{
inline geometry_msgs::msg::Point createMarkerPosition(double x, double y, double z)
{
  geometry_msgs::msg::Point point;
  point.x = x;
  point.y = y;
  point.z = z;
  return point;
}

inline geometry_msgs::msg::Quaternion createMarkerOrientation(
  double x, double y, double z, double w)
{
  geometry_msgs::msg::Quaternion quaternion;
  quaternion.x = x;
  quaternion.y = y;
  quaternion.z = z;
  quaternion.w = w;
  return quaternion;
}

inline geometry_msgs::msg::Vector3 createMarkerScale(double x, double y, double z)
{
  geometry_msgs::msg::Vector3 scale;
  scale.x = x;
  scale.y = y;
  scale.z = z;
  return scale;
}

inline std_msgs::msg::ColorRGBA createMarkerColor(float r, float g, float b, float a)
{
  std_msgs::msg::ColorRGBA color;
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
  return color;
}

inline visualization_msgs::msg::Marker createDefaultMarker(
  const std::string & frame_id, const rclcpp::Time & now, const std::string & ns, const int32_t id,
  const int32_t type, const geometry_msgs::msg::Vector3 & scale,
  const std_msgs::msg::ColorRGBA & color)
{
  visualization_msgs::msg::Marker marker;

  marker.header.frame_id = frame_id;
  marker.header.stamp = now;
  marker.ns = ns;
  marker.id = id;
  marker.type = type;
  marker.action = visualization_msgs::msg::Marker::ADD;
  marker.lifetime = rclcpp::Duration::from_seconds(0.5);

  marker.pose.position = createMarkerPosition(0.0, 0.0, 0.0);
  marker.pose.orientation = createMarkerOrientation(0.0, 0.0, 0.0, 1.0);
  marker.scale = scale;
  marker.color = color;
  marker.frame_locked = true;

  return marker;
}

inline visualization_msgs::msg::Marker createDeletedDefaultMarker(
  const rclcpp::Time & now, const std::string & ns, const int32_t id)
{
  visualization_msgs::msg::Marker marker;

  marker.header.stamp = now;
  marker.ns = ns;
  marker.id = id;
  marker.action = visualization_msgs::msg::Marker::DELETE;

  return marker;
}

inline void appendMarkerArray(
  const visualization_msgs::msg::MarkerArray & additional_marker_array,
  visualization_msgs::msg::MarkerArray * marker_array,
  const boost::optional<rclcpp::Time> & current_time = {})
{
  for (const auto & marker : additional_marker_array.markers) {
    marker_array->markers.push_back(marker);

    if (current_time) {
      marker_array->markers.back().header.stamp = current_time.get();
    }
  }
}
}  // namespace tier4_autoware_utils

#endif  // TIER4_AUTOWARE_UTILS__ROS__MARKER_HELPER_HPP_