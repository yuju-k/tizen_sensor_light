#include <sensor/environment_listener.h>
#include "hda_watch_face.h"
#include "bluetooth/gatt/characteristic.h"
#include <tools/sqlite_helper.h>

sensor_listener_h light_sensor_listener_handle = 0;
sensor_listener_h pedometer_listener_handle = 0;
sensor_listener_h pressure_sensor_listener_handle = 0;
sensor_listener_h sleep_monitor_listener_handle = 0;

unsigned int environment_sensor_listener_event_update_interval_ms = 1000;

char date_buf[64];

static void light_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data);
static void pedometer_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data);
static void pressure_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data);
static void sleep_monitor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data);

bool create_environment_sensor_listener(sensor_h light_sensor_handle,
		sensor_h pedometer_handle, sensor_h pressure_sensor_handle,
		sensor_h sleep_monitor_handle) {
	int retval;

	retval = sensor_create_listener(light_sensor_handle,
			&light_sensor_listener_handle);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}
	if (!set_light_sensor_listener_attribute()) {
		dlog_print(DLOG_ERROR, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a Light sensor listener.",
				__FILE__, __func__, __LINE__);
		return false;
	} else
		dlog_print(DLOG_INFO, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a Light sensor listener.",
				__FILE__, __func__, __LINE__);

	if (!set_light_sensor_listener_event_callback()) {
		dlog_print(DLOG_ERROR, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a Light sensor listener.",
				__FILE__, __func__, __LINE__);
		return false;
	} else
		dlog_print(DLOG_INFO, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a Light sensor listener.",
				__FILE__, __func__, __LINE__);

	retval = sensor_create_listener(pedometer_handle,
			&pedometer_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Function sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}
	if (!set_pedometer_listener_attribute()) {
		dlog_print(DLOG_ERROR, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a Pedometer listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a Pedometer listener.",
				__FILE__, __func__, __LINE__);

	if (!set_pedometer_listener_event_callback()) {
		dlog_print(DLOG_ERROR, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a Pedometer listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a Pedometer listener.",
				__FILE__, __func__, __LINE__);

	retval = sensor_create_listener(pressure_sensor_handle,
			&pressure_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
//		return false;
	}
	if (!set_pressure_sensor_listener_attribute()) {
		dlog_print(DLOG_ERROR, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a pressure sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a pressure sensor listener.",
				__FILE__, __func__, __LINE__);

	if (!set_pressure_sensor_listener_event_callback()) {
		dlog_print(DLOG_ERROR, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a pressure sensor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a pressure sensor listener.",
				__FILE__, __func__, __LINE__);

	//sleep_monitor
	retval = sensor_create_listener(sleep_monitor_handle,
			&sleep_monitor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Function sensor_create_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
//		return false;
	}
	if (!set_sleep_monitor_listener_attribute()) {
		dlog_print(DLOG_ERROR, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Failed to set an attribute to control the behavior of a sleep_monitor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Succeeded in setting an attribute to control the behavior of a sleep_monitor listener.",
				__FILE__, __func__, __LINE__);

	if (!set_sleep_monitor_listener_event_callback()) {
		dlog_print(DLOG_ERROR, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Failed to register the callback function to be invoked when sensor events are delivered via a sleep_monitor listener.",
				__FILE__, __func__, __LINE__);
//		return false;
	} else
		dlog_print(DLOG_INFO, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Succeeded in registering the callback function to be invoked when sensor events are delivered via a sleep_monitor listener.",
				__FILE__, __func__, __LINE__);

	return true;
}

//attribute//
bool set_light_sensor_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(light_sensor_listener_handle,
			SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_pedometer_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(pedometer_listener_handle,
			SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_pressure_sensor_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(pressure_sensor_listener_handle,
			SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

//set_sleep_monitor_listener_attribute
bool set_sleep_monitor_listener_attribute() {
	int retval;
	retval = sensor_listener_set_attribute_int(sleep_monitor_listener_handle,
			SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_attribute_int() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

//event_callback//
bool set_light_sensor_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(light_sensor_listener_handle,
			environment_sensor_listener_event_update_interval_ms,
			light_sensor_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_pedometer_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(pedometer_listener_handle, 0, pedometer_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_pressure_sensor_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(pressure_sensor_listener_handle,
			environment_sensor_listener_event_update_interval_ms,
			pressure_sensor_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

bool set_sleep_monitor_listener_event_callback() {
	int retval;
	retval = sensor_listener_set_event_cb(sleep_monitor_listener_handle, 0, sleep_monitor_listener_event_callback, NULL);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_set_event_cb() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else
		return true;
}

/////////// Setting sensor listener event callback ///////////
void light_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data) {

	char date_buf[64];
	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min,
			sec);

	dlog_print(DLOG_INFO, LIGHT_SENSOR_LOG_TAG,
			"%s/%s/%d: Function sensor_events_callback() output value = (%s, %llu, %f)",
			__FILE__, __func__, __LINE__, date_buf, events[0].timestamp,
			events[0].values[0]);

	char * filepath = get_write_filepath("hda_sensor_data.txt");
	char msg_data[512];
	snprintf(msg_data, 512,
			//"Light output value = (%s, %llu, %f)\n",
			"3,%s,%.0f\n", date_buf, events[0].values[0]);
	append_file(filepath, msg_data);

	for (int i = 0; i < events_count; i++) {
		float light_level = events[i].values[0];

		dlog_print(DLOG_INFO, ACCELEROMETER_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_events_callback() output value = %f",
				__FILE__, __func__, __LINE__, light_level);
	}
}

void pedometer_listener_event_callback(sensor_h sensor, sensor_event_s events[],
		int events_count, void *user_data) {

	char date_buf[64];
	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min, sec);

	char * state;

	sensor_pedometer_state_e pedometer_state = events[0].values[7];

	if (pedometer_state == SENSOR_PEDOMETER_STATE_RUN) {
		state = "2"; //RUN
	} else if (pedometer_state == SENSOR_PEDOMETER_STATE_STOP) {
		state = "0"; //STOP
	} else if (pedometer_state == SENSOR_PEDOMETER_STATE_WALK) {
		state = "1"; //Walk
	} else {
		state = "3"; //unknown
	}

	char * filepath = get_write_filepath("hda_sensor_data.txt");
	char msg_data[512];
	snprintf(msg_data, 512,
			//"Pedometer output value = (%s, %llu, %f, %f, %f, %f, %f, %f, %f, %s)\n",
			"0,%s,%f,%f,%f,%f,%f,%f,%f,%s\n",
			date_buf, events[0].values[0],
			events[0].values[1], events[0].values[2], events[0].values[3],
			events[0].values[4], events[0].values[5], events[0].values[6],
			state);
	append_file(filepath, msg_data);
}

void pressure_sensor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data) {

	char date_buf[64];
	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min,
			sec);

	char * filepath = get_write_filepath("hda_sensor_data.txt");
	char msg_data[512];
	snprintf(msg_data, 512,
			//"Pressure output value = (%s, %llu, %f)\n",
			"1,%s,%f\n", date_buf, events[0].values[0]);
	append_file(filepath, msg_data);
}

void sleep_monitor_listener_event_callback(sensor_h sensor,
		sensor_event_s events[], int events_count, void *user_data) {

	char date_buf[64];
	snprintf(date_buf, 64, "%d-%d-%d %d:%d:%d", year, month, day, hour, min,
			sec);

	char * state;
	sensor_sleep_state_e sleep_state = events[0].values[0];
	if (sleep_state == SENSOR_SLEEP_STATE_WAKE) {
		//state = "SENSOR_SLEEP_STATE_WAKE";
		state = "0"; //wake
	} else if (sleep_state == SENSOR_SLEEP_STATE_SLEEP) {
		//state = "SENSOR_SLEEP_STATE_SLEEP";
		state = "1"; //sleep
	} else {
		//state = "SENSOR_SLEEP_STATE_UNKNOWN";
		state = "2"; //unknown
	}

	char * filepath = get_write_filepath("hda_sensor_data.txt");
	char msg_data[512];
	snprintf(msg_data, 512,
			//"Sleep monitor output value = (%s, %llu, %s)\n",
			"2,%s,%s\n", date_buf, state);
	append_file(filepath, msg_data);
}

bool start_environment_sensor_listener() {
	int retval;
	retval = sensor_listener_start(light_sensor_listener_handle);
	dlog_print(DLOG_INFO, LIGHT_SENSOR_LOG_TAG, "%i : %s : %i", retval,
			get_error_message(retval), light_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}

	retval = sensor_listener_start(pedometer_listener_handle);
	dlog_print(DLOG_INFO, PEDOMETER_LOG_TAG, "%i : %s : %i", retval,
			get_error_message(retval), pedometer_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}

	retval = sensor_listener_start(pressure_sensor_listener_handle);
	dlog_print(DLOG_INFO, PRESSURE_SENSOR_LOG_TAG, "%i : %s : %i", retval,
			get_error_message(retval), pressure_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}

	retval = sensor_listener_start(sleep_monitor_listener_handle);
	dlog_print(DLOG_INFO, SLEEP_MONITOR_LOG_TAG, "%i : %s : %i", retval,
			get_error_message(retval), sleep_monitor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_ERROR, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_start() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}

	return true;

}

bool stop_environment_sensor_listener() {
	int retval;
	retval = sensor_listener_stop(light_sensor_listener_handle);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}

	retval = sensor_listener_stop(pedometer_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}

	retval = sensor_listener_stop(pressure_sensor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}

	retval = sensor_listener_stop(sleep_monitor_listener_handle);
	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Function sensor_listener_stop() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	}
	return true;
}

bool destroy_environment_sensor_listener() {
	int retval;
	retval = sensor_destroy_listener(light_sensor_listener_handle);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, LIGHT_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else {
		light_sensor_listener_handle = 0;
	}

	retval = sensor_destroy_listener(pedometer_listener_handle);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, PEDOMETER_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else {
		pedometer_listener_handle = 0;
	}

	retval = sensor_destroy_listener(pressure_sensor_listener_handle);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, PRESSURE_SENSOR_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else {
		pressure_sensor_listener_handle = 0;
	}

	retval = sensor_destroy_listener(sleep_monitor_listener_handle);

	if (retval != SENSOR_ERROR_NONE) {
		dlog_print(DLOG_INFO, SLEEP_MONITOR_LOG_TAG,
				"%s/%s/%d: Function sensor_destroy_listener() return value = %s",
				__FILE__, __func__, __LINE__, get_error_message(retval));
		return false;
	} else {
		sleep_monitor_listener_handle = 0;
	}
	return true;
}

bool check_environment_sensor_listener_is_created() {
	if (light_sensor_listener_handle == 0)
		return false;
	if (pedometer_listener_handle == 0)
		return false;
	if (pressure_sensor_listener_handle == 0)
		return false;
	if (sleep_monitor_listener_handle == 0)
		return false;
	else
		return true;

}
