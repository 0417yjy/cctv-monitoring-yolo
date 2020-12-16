#include "Falling.h"

FallenPerson::FallenPerson(bbox_t box, unsigned int frameno) {
	this->insertedFrame = 0;
	this->box = box;
}

unsigned int FallenPerson::getElapsedFrame(unsigned int currentFrame) {
	return currentFrame - insertedFrame;
}

unsigned int FallenPerson::getElapsedTime(unsigned int currentFrame, unsigned int fps) {
	if (fps == 0) {
		return 0;
	}
	else {
		return getElapsedFrame(currentFrame) / fps;
	}
}

bool FallenPerson::operator==(FallenPerson com) {
	if (this->box.x == com.box.x && this->box.y == com.box.y && this->box.w == com.box.w && this->box.h == com.box.h && this->box.obj_id == com.box.obj_id && this->box.track_id == com.box.track_id) {
		return true;
	}
	else {
		return false;

	}
}

FallingDetector::FallingDetector() {
	this->currentFrameNo = 0;
}

void FallingDetector::setCurrentFrameNo(unsigned int newFrame) {
	this->currentFrameNo = newFrame;
}

std::vector<bbox_t> FallingDetector::getBboxVector(std::vector<bbox_t>& result_vec, unsigned int class_no) {
	std::vector<bbox_t> returned_vec;
	
	for (auto i = result_vec.begin(); i != result_vec.end(); i++) {
		if (i->obj_id == class_no) {
			returned_vec.push_back(*i);
		}
	}

	return returned_vec;
}

bool FallingDetector::processDetectResult(std::vector<bbox_t>& result_vec, unsigned int frame_count) {
	if (frame_count > currentFrameNo) {
		std::vector<bbox_t> new_falling_list = getBboxVector(result_vec, FALLING_PERSON);
		std::vector<bbox_t> joined_falling_list(result_vec.size() + new_falling_list.size());
		// add to falling people list

		
		

		// get falling people from result_vec
		//std::set_union

		setCurrentFrameNo(frame_count);
		return false;
	}
	else {
		return false;
	}
}

bool FallingDetector::isEmergency() {
	for (int i = 0; i < fallenPersonList.size(); i++) {
		if (fallenPersonList[i].getElapsedTime(currentFrameNo, 55) >= EMERGENCY_TIME_THRESHOLD) {
			return true;
		}
	}
	return false;
}