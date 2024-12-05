#include <sensor/physics_listener.h>
#include <tools/sqlite_helper.h>
#include "hda_watch_face.h"
#include <app_preference.h>

sensor_listener_h accelerometer_sensor_listener_handle = 0;
sensor_listener_h gravity_sensor_listener_handle = 0;
sensor_listener_h gyroscope_rotation_vector_sensor_listener_handle = 0;
sensor_listener_h gyroscope_sensor_listener_handle = 0;
sensor_listener_h linear_acceleration_sensor_listener_handle = 0;
unsigned int physics_sensor_listener_event_update_interval_ms = 1000;

static void accelerometer_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data);
static void gravity_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data);
static void gyroscope_rotation_vector_sensor_listener_event_callback(
		sensor_h sensor, sensor_event_s events[], int events_count,
		void *user_data);
static void gyroscope_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data);
static void linear_acceleration_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data);

bool create_physics_sensor_listener(sensor_h accelerometer_sensor_handle,
		sensor_h gravity_sensor_handle,
		sensor_h gyroscope_rotation_vector_sensor_hanlde,
		sensor_h gyroscope_sensor_handle,
		sensor_h linear_acceleration_sensor_handle) {
	int retval;

	retval = sensor_create_listener(accelerometer_sensor_handle,
			&accelerometer_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Accelerometer sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}
	if (!set_accelerometer_sensor_listener_attribute()) {
		dlog_print(DLOG_ERROR, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a Accelerometer sensor listener.",
				__FILE__, __func__, __LINE__);
		return false;
	} else
		dlog_print(DLOG_INFO, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a Accelerometer sensor listener.",
				__FILE__, __func__, __LINE__);
	if (!set_accelerometer_sensor_listener_event_callback()) {
		dlog_print(DLOG_ERROR, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a Accelerometer sensor listener.",
				__FILE__, __func__, __LINE__);
		return false;
	} else
		dlog_print(DLOG_INFO, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a Accelerometer sensor listener.",
				__FILE__, __func__, __LINE__);

	retval = sensor_create_listener(gravity_sensor_handle,
			&gravity_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Gravity sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
//		return false;
	}
	if (!set_gravity_sensor_listener_attribute()) {
		dlog_print(DLOG_ERROR, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a Gravity sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a Gravity sensor listener.",
				__FILE__, __func__, __LINE__);
	if (!set_gravity_sensor_listener_event_callback()) {
		dlog_print(DLOG_ERROR, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a Gravity sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a Gravity sensor listener.",
				__FILE__, __func__, __LINE__);

	//gyroscope_rotation_vector
	retval = sensor_create_listener(gyroscope_rotation_vector_sensor_hanlde,
			&gyroscope_rotation_vector_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Gyroscope Rotation Vector sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
//		return false;
	}
	if (!set_gyroscope_rotation_vector_sensor_listener_attribute()) {
		dlog_print(DLOG_ERROR, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a Gyroscope Rotation vector sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a Gyroscope Rotation Vector sensor listener.",
				__FILE__, __func__, __LINE__);
	if (!set_gyroscope_rotation_vector_sensor_listener_event_callback()) {
		dlog_print(DLOG_ERROR, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a Gyroscope Rotation vector sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a Gyroscope Rotation vector sensor listener.",
				__FILE__, __func__, __LINE__);

	//gyroscope
	retval = sensor_create_listener(gyroscope_sensor_handle,
			&gyroscope_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Gyroscope sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
//		return false;
	}
	if (!set_gyroscope_sensor_listener_attribute()) {
		dlog_print(DLOG_ERROR, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a Gyroscope sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a Gyroscope sensor listener.",
				__FILE__, __func__, __LINE__);
	if (!set_gyroscope_sensor_listener_event_callback()) {
		dlog_print(DLOG_ERROR, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a Gyroscope sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a Gyroscope sensor listener.",
				__FILE__, __func__, __LINE__);

	//linear_acceleration_sensor
	retval = sensor_create_listener(linear_acceleration_sensor_handle,
			&linear_acceleration_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: linear_acceleration sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
//		return false;
	}
	if (!set_linear_acceleration_sensor_listener_attribute()) {
		dlog_print(DLOG_ERROR, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a linear_acceleration sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a linear_acceleration sensor listener.",
				__FILE__, __func__, __LINE__);
	if (!set_linear_acceleration_sensor_listener_event_callback()) {
		dlog_print(DLOG_ERROR, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a linear_acceleration sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a linear_acceleration sensor listener.",
				__FILE__, __func__, __LINE__);

	return true;
}

/////////// Setting sensor listener attribute ///////////

bool set_accelerometer_sensor_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(
			accelerometer_sensor_listener_handle, SENSOR_ATTRIBUTE_PAUSE_POLICY,
			SENSOR_PAUSE_NONE);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_gravity_sensor_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(gravity_sensor_listener_handle,
			SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_gyroscope_rotation_vector_sensor_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(
			gyroscope_rotation_vector_sensor_listener_handle,
			SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_gyroscope_sensor_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(gyroscope_sensor_listener_handle,
			SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_linear_acceleration_sensor_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(
			linear_acceleration_sensor_listener_handle,
			SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

/////////// Setting sensor listener event callback ///////////

bool set_accelerometer_sensor_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(accelerometer_sensor_listener_handle,
			physics_sensor_listener_event_update_interval_ms,
			accelerometer_sensor_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_gravity_sensor_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(gravity_sensor_listener_handle,
			physics_sensor_listener_event_update_interval_ms,
			gravity_sensor_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_gyroscope_rotation_vector_sensor_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(
			gyroscope_rotation_vector_sensor_listener_handle,
			physics_sensor_listener_event_update_interval_ms,
			gyroscope_rotation_vector_sensor_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_gyroscope_sensor_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(gyroscope_sensor_listener_handle,
			physics_sensor_listener_event_update_interval_ms,
			gyroscope_sensor_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_linear_acceleration_sensor_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(
			linear_acceleration_sensor_listener_handle,
			physics_sensor_listener_event_update_interval_ms,
			linear_acceleration_sensor_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

/////////// Setting sensor listener event callback ///////////

//void accelerometer_sensor_listener_event_callback(sensor_h sensor,
//		sensor_event_s events[], int events_count, void *user_data) {
//
//	char date_buf[64];
//	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min, sec);
//
//	char * filepath = get_write_filepath("hda_sensor_data.txt");
//	char msg_data[512];
//	snprintf(msg_data, 512,
//			//"Accelerometer output value = (%s, %llu, %f, %f, %f)\n",
//			"6,%s,%f,%f,%f\n",
//			date_buf,events[0].values[0], events[0].values[1], events[0].values[2]);
//	append_file(filepath, msg_data);
//
//	for (int i = 1; i < events_count; i++) {
//		//unsigned long long timestamp = events[i].timestamp;
//		//int accuracy = events[i].accuracy;
//		float x = events[i].values[0];
//		float y = events[i].values[1];
//		float z = events[i].values[2];
//
//		dlog_print(DLOG_INFO, ACCELEROMETER_SENSOR_LOG_TAG,
//				"%s/%s/%d: Function sensor_events_callback() output value = (%f, %f, %f)",
//				__FILE__, __func__, __LINE__, x, y, z);
//	}
//}

void accelerometer_sensor_listener_event_callback(sensor_h sensor,
                                                  sensor_event_s events[],
                                                  int events_count, void *user_data) {
	char timestamp_date_buf[64];
	struct tm *timeinfo;
	time_t current_time;
	time_t seconds;
	unsigned long long timestamp_ns = events[0].timestamp;

	// 현재 시간을 기준으로 보정
	time(&current_time); // 현재 시간 (초 단위)
	seconds = current_time + (timestamp_ns / 1000000000); // 현재 시간에 상대적 timestamp 추가
	unsigned long milliseconds = (timestamp_ns % 1000000000) / 1000000;

	// 초 단위를 struct tm으로 변환
	timeinfo = localtime(&seconds);

	// 변환된 날짜와 시간 저장 (밀리초 포함)
//	snprintf(timestamp_date_buf, 64, "%04d-%02d-%02d %02d:%02d:%02d.%03lu",
//			 timeinfo->tm_year + 1900,
//			 timeinfo->tm_mon + 1,
//			 timeinfo->tm_mday,
//			 timeinfo->tm_hour,
//			 timeinfo->tm_min,
//			 timeinfo->tm_sec,
//			 milliseconds);

	snprintf(timestamp_date_buf, 64, "%02d-%02d %02d:%02d:%02d.%03lu",
			 timeinfo->tm_mon + 1,
			 timeinfo->tm_mday,
			 timeinfo->tm_hour,
			 timeinfo->tm_min,
			 timeinfo->tm_sec,
			 milliseconds);

    char *filepath = get_write_filepath("hda_sensor_data.txt");
    char msg_data[512];
    snprintf(msg_data, 512,
             "6,%s,%f,%f,%f\n",
             timestamp_date_buf, events[0].values[0], events[0].values[1], events[0].values[2]);
    append_file(filepath, msg_data);

//    for (int i = 1; i < events_count; i++) {
//        float x = events[i].values[0];
//        float y = events[i].values[1];
//        float z = events[i].values[2];
//    }
}

//void gravity_sensor_listener_event_callback(sensor_h sensor,
//		sensor_event_s events[], int events_count, void *user_data) {
//
//	char date_buf[64];
//	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min,
//			sec);
//
//	char * filepath = get_write_filepath("hda_sensor_data.txt");
//	char msg_data[512];
//	snprintf(msg_data, 512,
//			//"Gravity output value = (%s, %llu, %f, %f, %f)\n",
//			"7,%s,%f,%f,%f\n",
//			date_buf, events[0].values[0], events[0].values[1], events[0].values[2]);
//	append_file(filepath, msg_data);
//
//	for (int i = 1; i < events_count; i++) {
//		//unsigned long long timestamp = events[i].timestamp;
//		//int accuracy = events[i].accuracy;
//		float x = events[i].values[0];
//		float y = events[i].values[1];
//		float z = events[i].values[2];
//	}
//}

void gravity_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data) {

	char timestamp_date_buf[64];
	struct tm *timeinfo;
	time_t current_time;
	time_t seconds;
	unsigned long long timestamp_ns = events[0].timestamp;

	// 현재 시간을 기준으로 보정
	time(&current_time); // 현재 시간 (초 단위)
	seconds = current_time + (timestamp_ns / 1000000000); // 현재 시간에 상대적 timestamp 추가
	unsigned long milliseconds = (timestamp_ns % 1000000000) / 1000000;

	// 초 단위를 struct tm으로 변환
	timeinfo = localtime(&seconds);

	// 변환된 날짜와 시간 저장 (밀리초 포함)
//	snprintf(timestamp_date_buf, 64, "%04d-%02d-%02d %02d:%02d:%02d.%03lu",
//			 timeinfo->tm_year + 1900,
//			 timeinfo->tm_mon + 1,
//			 timeinfo->tm_mday,
//			 timeinfo->tm_hour,
//			 timeinfo->tm_min,
//			 timeinfo->tm_sec,
//			 milliseconds);

	snprintf(timestamp_date_buf, 64, "%02d-%02d %02d:%02d:%02d.%03lu",
			 timeinfo->tm_mon + 1,
			 timeinfo->tm_mday,
			 timeinfo->tm_hour,
			 timeinfo->tm_min,
			 timeinfo->tm_sec,
			 milliseconds);

	char * filepath = get_write_filepath("hda_sensor_data.txt");
	char msg_data[512];
	snprintf(msg_data, 512,
			//"Gravity output value = (%s, %llu, %f, %f, %f)\n",
			"7,%s,%f,%f,%f\n",
			timestamp_date_buf, events[0].values[0], events[0].values[1], events[0].values[2]);
	append_file(filepath, msg_data);
}

//void gyroscope_rotation_vector_sensor_listener_event_callback(sensor_h sensor,
//		sensor_event_s events[], int events_count, void *user_data) {
//
//	char date_buf[64];
//	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min,
//			sec);
//
//	char * filepath = get_write_filepath("hda_sensor_data.txt");
//	char msg_data[512];
//	snprintf(msg_data, 512,
//			//"Gyroscope rotation vector output value = (%s, %llu, %d, %f, %f, %f, %f)\n",
//			"8,%s,%d,%f,%f,%f,%f\n",
//			date_buf, events[0].accuracy, events[0].values[0], events[0].values[1], events[0].values[2],events[0].values[3]);
//	append_file(filepath, msg_data);
//
//	for (int i = 1; i < events_count; i++) {
//		//unsigned long long timestamp = events[i].timestamp;
//		//int accuracy = events[i].accuracy;
//		float x = events[i].values[0];
//		float y = events[i].values[1];
//		float z = events[i].values[2];
//		float w = events[i].values[3];
//	}
//}

void gyroscope_rotation_vector_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data) {

	char timestamp_date_buf[64];
	struct tm *timeinfo;
	time_t current_time;
	time_t seconds;
	unsigned long long timestamp_ns = events[0].timestamp;

	// 현재 시간을 기준으로 보정
	time(&current_time); // 현재 시간 (초 단위)
	seconds = current_time + (timestamp_ns / 1000000000); // 현재 시간에 상대적 timestamp 추가
	unsigned long milliseconds = (timestamp_ns % 1000000000) / 1000000;

	// 초 단위를 struct tm으로 변환
	timeinfo = localtime(&seconds);

	// 변환된 날짜와 시간 저장 (밀리초 포함)
//	snprintf(timestamp_date_buf, 64, "%04d-%02d-%02d %02d:%02d:%02d.%03lu",
//			 timeinfo->tm_year + 1900,
//			 timeinfo->tm_mon + 1,
//			 timeinfo->tm_mday,
//			 timeinfo->tm_hour,
//			 timeinfo->tm_min,
//			 timeinfo->tm_sec,
//			 milliseconds);

	snprintf(timestamp_date_buf, 64, "%02d-%02d %02d:%02d:%02d.%03lu",
			 timeinfo->tm_mon + 1,
			 timeinfo->tm_mday,
			 timeinfo->tm_hour,
			 timeinfo->tm_min,
			 timeinfo->tm_sec,
			 milliseconds);

	char * filepath = get_write_filepath("hda_sensor_data.txt");
	char msg_data[512];
	snprintf(msg_data, 512,
			//"Gyroscope rotation vector output value = (%s, %llu, %d, %f, %f, %f, %f)\n",
			"8,%s,%d,%f,%f,%f,%f\n",
			timestamp_date_buf, events[0].accuracy, events[0].values[0], events[0].values[1], events[0].values[2],events[0].values[3]);
	append_file(filepath, msg_data);

//	for (int i = 1; i < events_count; i++) {
//		//unsigned long long timestamp = events[i].timestamp;
//		//int accuracy = events[i].accuracy;
//		float x = events[i].values[0];
//		float y = events[i].values[1];
//		float z = events[i].values[2];
//		float w = events[i].values[3];
//	}
}

//void gyroscope_sensor_listener_event_callback(sensor_h sensor,
//		sensor_event_s events[], int events_count, void *user_data) {
//
//	char date_buf[64];
//	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min,
//			sec);
//
//	char * filepath = get_write_filepath("hda_sensor_data.txt");
//	char msg_data[512];
//	snprintf(msg_data, 512,
//			//"Gyroscope output value = (%s, %llu, %f, %f, %f)\n",
//			"9,%s,%.2f,%.2f,%.2f\n",
//			date_buf, events[0].values[0], events[0].values[1], events[0].values[2]);
//	append_file(filepath, msg_data);
//
//	for (int i = 1; i < events_count; i++) {
//		//unsigned long long timestamp = events[i].timestamp;
//		//int accuracy = events[i].accuracy;
//		float x = events[i].values[0];
//		float y = events[i].values[1];
//		float z = events[i].values[2];
//	}
//}

void gyroscope_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data) {

	char timestamp_date_buf[64];
	struct tm *timeinfo;
	time_t current_time;
	time_t seconds;
	unsigned long long timestamp_ns = events[0].timestamp;

	// 현재 시간을 기준으로 보정
	time(&current_time); // 현재 시간 (초 단위)
	seconds = current_time + (timestamp_ns / 1000000000); // 현재 시간에 상대적 timestamp 추가
	unsigned long milliseconds = (timestamp_ns % 1000000000) / 1000000;

	// 초 단위를 struct tm으로 변환
	timeinfo = localtime(&seconds);

	// 변환된 날짜와 시간 저장 (밀리초 포함)
//	snprintf(timestamp_date_buf, 64, "%04d-%02d-%02d %02d:%02d:%02d.%03lu",
//			 timeinfo->tm_year + 1900,
//			 timeinfo->tm_mon + 1,
//			 timeinfo->tm_mday,
//			 timeinfo->tm_hour,
//			 timeinfo->tm_min,
//			 timeinfo->tm_sec,
//			 milliseconds);

	snprintf(timestamp_date_buf, 64, "%02d-%02d %02d:%02d:%02d.%03lu",
			 timeinfo->tm_mon + 1,
			 timeinfo->tm_mday,
			 timeinfo->tm_hour,
			 timeinfo->tm_min,
			 timeinfo->tm_sec,
			 milliseconds);

	char * filepath = get_write_filepath("hda_sensor_data.txt");
	char msg_data[512];
	snprintf(msg_data, 512,
			//"Gyroscope output value = (%s, %llu, %f, %f, %f)\n",
			"9,%s,%.2f,%.2f,%.2f\n",
			timestamp_date_buf, events[0].values[0], events[0].values[1], events[0].values[2]);
	append_file(filepath, msg_data);

//	for (int i = 1; i < events_count; i++) {
//		//unsigned long long timestamp = events[i].timestamp;
//		//int accuracy = events[i].accuracy;
//		float x = events[i].values[0];
//		float y = events[i].values[1];
//		float z = events[i].values[2];
//	}
}

//void linear_acceleration_sensor_listener_event_callback(sensor_h sensor,
//		sensor_event_s events[], int events_count, void *user_data) {
//
//	char date_buf[64];
//	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min,
//			sec);
//
//	char * filepath = get_write_filepath("hda_sensor_data.txt");
//	char msg_data[512];
//	snprintf(msg_data, 512,
//			//"Linear acceleration output value = (%s, %llu, %f, %f, %f)\n",
//			"10,%s,%f,%f,%f\n",
//			date_buf, events[0].values[0], events[0].values[1], events[0].values[2]);
//	append_file(filepath, msg_data);
//
//	for (int i = 1; i < events_count; i++) {
//		//unsigned long long timestamp = events[i].timestamp;
//		//int accuracy = events[i].accuracy;
//		float x = events[i].values[0];
//		float y = events[i].values[1];
//		float z = events[i].values[2];
//	}
//}

void linear_acceleration_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data) {

	char timestamp_date_buf[64];
	struct tm *timeinfo;
	time_t current_time;
	time_t seconds;
	unsigned long long timestamp_ns = events[0].timestamp;

	// 현재 시간을 기준으로 보정
	time(&current_time); // 현재 시간 (초 단위)
	seconds = current_time + (timestamp_ns / 1000000000); // 현재 시간에 상대적 timestamp 추가
	unsigned long milliseconds = (timestamp_ns % 1000000000) / 1000000;

	// 초 단위를 struct tm으로 변환
	timeinfo = localtime(&seconds);

	// 변환된 날짜와 시간 저장 (밀리초 포함)
//	snprintf(timestamp_date_buf, 64, "%04d-%02d-%02d %02d:%02d:%02d.%03lu",
//			 timeinfo->tm_year + 1900,
//			 timeinfo->tm_mon + 1,
//			 timeinfo->tm_mday,
//			 timeinfo->tm_hour,
//			 timeinfo->tm_min,
//			 timeinfo->tm_sec,
//			 milliseconds);

	snprintf(timestamp_date_buf, 64, "%02d-%02d %02d:%02d:%02d.%03lu",
			 timeinfo->tm_mon + 1,
			 timeinfo->tm_mday,
			 timeinfo->tm_hour,
			 timeinfo->tm_min,
			 timeinfo->tm_sec,
			 milliseconds);

	char * filepath = get_write_filepath("hda_sensor_data.txt");
	char msg_data[512];
	snprintf(msg_data, 512,
			//"Linear acceleration output value = (%s, %llu, %f, %f, %f)\n",
			"10,%s,%f,%f,%f\n",
			timestamp_date_buf, events[0].values[0], events[0].values[1], events[0].values[2]);
	append_file(filepath, msg_data);
}

/////////// Setting sensor listener event callback ///////////

bool start_physics_sensor_listener() {
	int accelerometer_retval;
	accelerometer_retval = sensor_listener_start(
			accelerometer_sensor_listener_handle);
	if (accelerometer_retval == 0)
		dlog_print(DLOG_INFO, ACCELEROMETER_SENSOR_LOG_TAG, "%i : %s : %i",
				accelerometer_retval, get_error_message(accelerometer_retval),
				accelerometer_sensor_listener_handle);
	else
		dlog_print(DLOG_WARN, ACCELEROMETER_SENSOR_LOG_TAG, "%i : %s : %i",
				accelerometer_retval, get_error_message(accelerometer_retval),
				accelerometer_sensor_listener_handle);

	if (accelerometer_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(accelerometer_retval));
		return false;
	}

	int gravity_retval;
	gravity_retval = sensor_listener_start(gravity_sensor_listener_handle);
	if (gravity_retval == 0)
		dlog_print(DLOG_INFO, GRAVITY_SENSOR_LOG_TAG, "%i : %s : %i",
				gravity_retval, get_error_message(gravity_retval),
				gravity_sensor_listener_handle);
	else
		dlog_print(DLOG_WARN, GRAVITY_SENSOR_LOG_TAG, "%i : %s : %i",
				gravity_retval, get_error_message(gravity_retval),
				gravity_sensor_listener_handle);

	if (gravity_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gravity_retval));
//		return false;
	}

	int gyroscope_rotation_vector_retval;
	gyroscope_rotation_vector_retval = sensor_listener_start(
			gyroscope_rotation_vector_sensor_listener_handle);
	if (gyroscope_rotation_vector_retval == 0)
		dlog_print(DLOG_INFO, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%i : %s : %i", gyroscope_rotation_vector_retval,
				get_error_message(gyroscope_rotation_vector_retval),
				gyroscope_rotation_vector_sensor_listener_handle);
	else
		dlog_print(DLOG_WARN, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%i : %s : %i", gyroscope_rotation_vector_retval,
				get_error_message(gyroscope_rotation_vector_retval),
				gyroscope_rotation_vector_sensor_listener_handle);

	if (gyroscope_rotation_vector_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gyroscope_rotation_vector_retval));
//			return false;
	}

	int gyroscope_retval;
	gyroscope_retval = sensor_listener_start(gyroscope_sensor_listener_handle);
	if (gyroscope_retval == 0)
		dlog_print(DLOG_INFO, GYROSCOPE_SENSOR_LOG_TAG, "%i : %s : %i",
				gyroscope_retval, get_error_message(gyroscope_retval),
				gyroscope_sensor_listener_handle);
	else
		dlog_print(DLOG_WARN, GYROSCOPE_SENSOR_LOG_TAG, "%i : %s : %i",
				gyroscope_retval, get_error_message(gyroscope_retval),
				gyroscope_sensor_listener_handle);

	if (gyroscope_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gyroscope_retval));
//		return false;
	}

	int linear_acceleration_retval;
	linear_acceleration_retval = sensor_listener_start(
			linear_acceleration_sensor_listener_handle);
	if (linear_acceleration_retval == 0)
		dlog_print(DLOG_INFO, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%i : %s : %i", linear_acceleration_retval,
				get_error_message(linear_acceleration_retval),
				linear_acceleration_sensor_listener_handle);
	else
		dlog_print(DLOG_WARN, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%i : %s : %i", linear_acceleration_retval,
				get_error_message(linear_acceleration_retval),
				linear_acceleration_sensor_listener_handle);

	if (linear_acceleration_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(linear_acceleration_retval));
		//		return false;
	}

	return true;
}

bool stop_physics_sensor_listener() {
	int accelerometer_retval;
	accelerometer_retval = sensor_listener_stop(
			accelerometer_sensor_listener_handle);
	if (accelerometer_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(accelerometer_retval));
		return false;
	}

	int gravity_retval;
	gravity_retval = sensor_listener_stop(gravity_sensor_listener_handle);
	if (gravity_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gravity_retval));
		return false;
	}

	int gyroscope_rotation_vector_retval;
	gyroscope_rotation_vector_retval = sensor_listener_stop(
			gyroscope_rotation_vector_sensor_listener_handle);
	if (gyroscope_rotation_vector_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gyroscope_rotation_vector_retval));
		return false;
	}

	int gyroscope_retval;
	gyroscope_retval = sensor_listener_stop(gyroscope_sensor_listener_handle);
	if (gyroscope_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gyroscope_retval));
		return false;
	}

	int linear_acceleration_retval;
	linear_acceleration_retval = sensor_listener_stop(
			linear_acceleration_sensor_listener_handle);
	if (linear_acceleration_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(linear_acceleration_retval));
		return false;
	}

	return true;
}

bool destroy_physics_sensor_listener() {
	int accelerometer_retval;
	accelerometer_retval = sensor_destroy_listener(
			accelerometer_sensor_listener_handle);

	if (accelerometer_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(accelerometer_retval));
		return false;
	} else {
		accelerometer_sensor_listener_handle = 0;
	}

	int gravity_retval;
	gravity_retval = sensor_destroy_listener(gravity_sensor_listener_handle);

	if (gravity_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GRAVITY_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gravity_retval));
		return false;
	} else {
		gravity_sensor_listener_handle = 0;
	}

	int gyroscope_rotation_vector_retval;
	gyroscope_rotation_vector_retval = sensor_destroy_listener(
			gyroscope_rotation_vector_sensor_listener_handle);

	if (gyroscope_rotation_vector_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_ROTATION_VECTOR_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gyroscope_rotation_vector_retval));
		return false;
	} else {
		gyroscope_rotation_vector_sensor_listener_handle = 0;
	}

	int gyroscope_retval;
	gyroscope_retval = sensor_destroy_listener(
			gyroscope_sensor_listener_handle);

	if (gyroscope_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, GYROSCOPE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(gyroscope_retval));
		return false;
	} else {
		gyroscope_sensor_listener_handle = 0;
	}

	int linear_acceleration_retval;
	linear_acceleration_retval = sensor_destroy_listener(
			linear_acceleration_sensor_listener_handle);

	if (linear_acceleration_retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LINEAR_ACCELERATION_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__,
				get_error_message(linear_acceleration_retval));
		return false;
	} else {
		linear_acceleration_sensor_listener_handle = 0;
	}

	return true;
}

bool check_physics_sensor_listener_is_created() {
	if (accelerometer_sensor_listener_handle == 0)
		return false;
	if (gravity_sensor_listener_handle == 0)
		return false;
	if (gyroscope_rotation_vector_sensor_listener_handle == 0)
		return false;
	if (gyroscope_sensor_listener_handle == 0)
		return false;
	if (linear_acceleration_sensor_listener_handle == 0)
		return false;
	return true;
}
