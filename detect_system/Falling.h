#pragma once
#include "yolo_v2_class.hpp"
#include <vector>
#define EMERGENCY_TIME_THRESHOLD 5

enum person_class_id {
	FALLING_PERSON,
	FALLEN_PERSON,
	SITTING_PERSON,
	PICKING_PERSON,
	PERSON
};

class FallenPerson {
	bbox_t box;
	unsigned int insertedFrame;
	bool abnormal;
	bool emergency_reported;

	bool available;
	unsigned int no_show_frame;
public:
	FallenPerson(bbox_t box, unsigned int frameno, bool abnormal);
	bbox_t getBox();
	unsigned int getElapsedFrame(unsigned int currentFrame);
	unsigned int getElapsedTime(unsigned int currentFrame, unsigned int fps);
	void setAvailable(bool b);
	bool isAvailable();
	void setReported(bool b);
	bool isReported();
	bool equalObj(bbox_t com);
	// void incrementFrame();
	bool isExpired();
};

class FallingDetector {
	std::vector<bbox_t> fallingPersonList;
	std::vector<FallenPerson> fallenPersonList;
	unsigned int currentFrameNo;

	void setCurrentFrameNo(unsigned int newFrame);
	std::vector<bbox_t> getBboxVector(std::vector<bbox_t>& result_vec, unsigned int class_no);
	bool areBoxesSame(bbox_t falling_obj, bbox_t fallen_obj, float threshold);

	int framerate;
public:
	FallingDetector(int fps);
	int processDetectResult(std::vector<bbox_t>& result_vec, unsigned int frame_count);
	bool isEmergency();
	void dumpList();
};