#pragma once
#include "yolo_v2_class.hpp"
#include <vector>
#define EMERGENCY_TIME_THRESHOLD 5

enum falling_class_id {
	FALLING_PERSON,
	FALLEN_PERSON,
	SITTING_PERSON,
	PICKING_PERSON
};

class FallenPerson {
	bbox_t box;
	unsigned int insertedFrame;
public:
	FallenPerson(bbox_t box, unsigned int frameno);
	unsigned int getElapsedFrame(unsigned int currentFrame);
	unsigned int getElapsedTime(unsigned int currentFrame, unsigned int fps);
	bool operator==(FallenPerson com);
};

class FallingDetector {
	std::vector<bbox_t> fallingPersonList;
	std::vector<FallenPerson> fallenPersonList;
	unsigned int currentFrameNo;
	void setCurrentFrameNo(unsigned int newFrame);
	std::vector<bbox_t> getBboxVector(std::vector<bbox_t>& result_vec, unsigned int class_no);
public:
	FallingDetector();
	bool processDetectResult(std::vector<bbox_t>& result_vec, unsigned int frame_count);
	bool isEmergency();
};