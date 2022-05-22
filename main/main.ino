#define LEFT_LED 11
#define RIGHT_LED 12

#define LINE_TRACER_OUTER_RIGHT 0
#define LINE_TRACER_INNER_RIGHT 1
#define LINE_TRACER_INNER_LEFT 2
#define LINE_TRACER_OUTER_LEFT 3

#define LINE_TRACER_TRUE_VOLTAG 350

bool old_outer_right = false;
bool old_inner_right = false;
bool old_outer_left = false;
bool old_inner_left = false;
bool traveling_direction_left = true;
#define DELAY_TIME 50

void right_turn(int delay_time = DELAY_TIME) {
	// Serial.println("右回転");
	digitalWrite(RIGHT_LED, HIGH);
	digitalWrite(LEFT_LED, HIGH);
	delay(delay_time);
	digitalWrite(RIGHT_LED, LOW);
	digitalWrite(LEFT_LED, LOW);
}

void left_turn(int delay_time = DELAY_TIME) {
	// Serial.println("左回転");
	digitalWrite(RIGHT_LED, LOW);
	digitalWrite(LEFT_LED, HIGH);
	delay(delay_time);
	digitalWrite(RIGHT_LED, LOW);
	digitalWrite(LEFT_LED, LOW);
}

void through(int delay_time = DELAY_TIME) {
	// Serial.println("直進");
	digitalWrite(RIGHT_LED, LOW);
	digitalWrite(LEFT_LED, LOW);
	delay(delay_time);
	digitalWrite(RIGHT_LED, LOW);
	digitalWrite(LEFT_LED, LOW);
}

void back(int delay_time = DELAY_TIME) {
	// Serial.println("後退");
	digitalWrite(RIGHT_LED, HIGH);
	digitalWrite(LEFT_LED, LOW);
	delay(delay_time);
	digitalWrite(RIGHT_LED, LOW);
	digitalWrite(LEFT_LED, LOW);
}

void left_go() {
	back(200);
	delay(20);
	left_turn(200);
}
void right_go() {
	back(200);
	delay(20);
	right_turn(200);
}

/*
	return bool 黒ライン上で赤LED点灯=true 消灯でfalse
*/
bool is_black_line_tracer_outer_right() {
	int val = analogRead(LINE_TRACER_OUTER_RIGHT);
	return (val > LINE_TRACER_TRUE_VOLTAG) ? true : false;
}
bool is_black_line_tracer_inner_right() {
	int val = analogRead(LINE_TRACER_INNER_RIGHT);
	return (val > LINE_TRACER_TRUE_VOLTAG) ? true : false;
}
bool is_black_line_tracer_outer_left() {
	int val = analogRead(LINE_TRACER_OUTER_LEFT);
	return (val > LINE_TRACER_TRUE_VOLTAG) ? true : false;
}
bool is_black_line_tracer_inner_left() {
	int val = analogRead(LINE_TRACER_INNER_LEFT);
	return (val > LINE_TRACER_TRUE_VOLTAG) ? true : false;
}

void setup() {
	Serial.begin(115200);
	pinMode(LEFT_LED, OUTPUT);
	pinMode(RIGHT_LED, OUTPUT);
}

bool test = false;
void loop() {
	bool outer_right = is_black_line_tracer_outer_right();
	bool inner_right = is_black_line_tracer_inner_right();
	bool outer_left = is_black_line_tracer_outer_left();
	bool inner_left = is_black_line_tracer_inner_left();
	Serial.println(String(outer_left) + ":" + String(inner_left) + "↑" + String(inner_right) + ":" +
				   String(outer_right));
	test = !test;
	if (outer_left && inner_left) {
		if (outer_right && inner_right) {
			Serial.println("前方はすべて黒");
			left_go();
		} else {
			Serial.println("右方向転換");
			right_go();
		}
	} else {
		if (outer_right && inner_right) {
			Serial.println("左方向転換");
			left_go();
		} else {
			Serial.println("直進");
			through();
		}
	}
	// if (outer_left && inner_left && outer_right && inner_right) {
	// 	Serial.println("left");
	// 	// left_turn(200);
	// 	left_go();
	// } else {
	// 	Serial.println("right");
	// 	// right_turn(200);
	// 	right_go();
	// }

	// if (outer_right && inner_right && outer_left && inner_left) {
	// 	// 前方全部が黒
	// 	Serial.println("前方はすべて黒");
	// 	back();
	// 	delay(100);
	// 	if (old_outer_right || old_inner_right) {
	// 		left_turn();
	// 		delay(100);
	// 	} else if (old_outer_left || old_inner_left) {
	// 		right_turn();
	// 		delay(100);
	// 	} else {
	// 		left_turn();
	// 		delay(100);
	// 	}
	// } else if (!outer_right && !inner_right && !outer_left && !inner_left) {
	// 	// 前方全部が白
	// 	Serial.println("直進");
	// 	through();
	// 	delay(100);
	// } else if (outer_right || inner_right) {
	// 	Serial.println("左方向転換");
	// 	back();
	// 	delay(100);
	// 	left_turn();
	// 	delay(300);
	// } else if (outer_left || inner_left) {
	// 	Serial.println("右旋回");
	// 	back();
	// 	delay(100);
	// 	right_turn();
	// 	delay(300);
	// }
	// old_outer_right = outer_right;
	// old_inner_right = inner_right;
	// old_outer_left = outer_left;
	// old_inner_left = inner_left;
}