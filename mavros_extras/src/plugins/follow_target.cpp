/**
 * @brief SetpointFollowTarget plugin
 * @file setpoint_follow_target.cpp
 * @author snow pang <18516614106@163.com>
 *
 * @addtogroup plugin
 * @{
 */

#include <mavros/mavros_plugin.h>
#include <tf2_eigen/tf2_eigen.h>
#include <boost/algorithm/string.hpp>

#include <mavros_msgs/FollowTarget.h>

namespace mavros {
namespace extra_plugins {

/**
 * @brief Setpoint Follow Target plugin
 *
 * Receive follow target setpoints and send setpoint_follow_target mavlink msg.
 */
class FollowTargetPlugin : public plugin::PluginBase{
public:
	FollowTargetPlugin() : PluginBase(),
		sp_nh("~follow_target")
	{ }

	void initialize(UAS &uas_) override
	{
		PluginBase::initialize(uas_);

		target_sub = sp_nh.subscribe("target_localization", 10, &FollowTargetPlugin::follow_target_cb, this);
	}

	Subscriptions get_subscriptions() override
	{
		return { /* Rx disabled */ };
	}

private:
  ros::NodeHandle sp_nh;
  ros::Subscriber target_sub;

	/* -*- callbacks -*- */

	void follow_target_cb(const mavros_msgs::FollowTarget::ConstPtr &req)
	{
		mavlink::common::msg::FOLLOW_TARGET msg{};

		// Read first duration of the setpoint and set the timer
		msg.lat = int32_t(req->latitude*1e7);
    msg.lon = int32_t(req->longitude*1e7);
    msg.alt = req->altitude;
    msg.vel[0] = req->vx;
    msg.vel[1] = req->vy;
    msg.vel[2] = req->vz;

    // ROS_INFO_STREAM_NAMED("odom", "follow_target_cb" << std::endl);

    UAS_FCU(m_uas)->send_message_ignore_drop(msg);
	}
};
}	// namespace extra_plugins
}	// namespace mavros

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(mavros::extra_plugins::FollowTargetPlugin, mavros::plugin::PluginBase)
