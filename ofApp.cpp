#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float R = 300;
	int v_span = 4;
	int u_span = 8;

	for (int v = 0; v < 360; v += v_span) {

		for (auto u = 0; u < 360; u += u_span) {

			auto r = 80.f;
			auto noise_value = ofNoise(glm::vec4(this->make_point(R, 90, u + u_span * 0.5, v) * 0.01, ofGetFrameNum() * 0.008));
			if (noise_value < 0.3) { r = ofMap(noise_value, 0, 0.3, 10, 80); }
			if (noise_value > 0.7) { r = ofMap(noise_value, 0.7, 1, 80, 200); }

			vector<glm::vec3> vertices;
			vertices.push_back(this->make_point(R, r, u, v - v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u + u_span, v - v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u + u_span, v + v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u, v + v_span * 0.5));

			int index = face.getNumVertices();
			this->face.addVertices(vertices);

			this->face.addIndex(index + 0); face.addIndex(index + 1); face.addIndex(index + 2);
			this->face.addIndex(index + 0); face.addIndex(index + 2); face.addIndex(index + 3);

			this->frame.addVertices(vertices);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
			this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);
			this->frame.addIndex(index + 3); this->frame.addIndex(index + 0);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.37);
	ofRotateY(ofGetFrameNum() * 0.72);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}