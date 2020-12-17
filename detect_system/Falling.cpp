#include "Falling.h"
#include <algorithm>
#include <cmath>
#define THRESHOLD_VALUE 0.8
#define NO_SHOW_THRESHOLD 3

FallenPerson::FallenPerson(bbox_t box, unsigned int frameno, bool abnormal=false) {
	this->box = box;
	this->insertedFrame = frameno;
	this->abnormal = abnormal;
	this->emergency_reported = false;
	this->available = false;
	this->no_show_frame = 0;
}

bbox_t FallenPerson::getBox()
{
	return box;
}

unsigned int FallenPerson::getElapsedFrame(unsigned int currentFrame) {
	return currentFrame - insertedFrame;
}

unsigned int FallenPerson::getElapsedTime(unsigned int currentFrame, unsigned int fps) {
	if (fps == 0) {
		return 0;
	}
	else {
		/*std::cout << "insertedFrame: " << insertedFrame << std::endl;
		std::cout << "currentFrame: " << currentFrame << std::endl;*/
		return getElapsedFrame(currentFrame) / fps;
	}
}

void FallenPerson::setAvailable(bool b)
{
	this->available = b;
	if (b) {
		no_show_frame = 0; // available �ϸ� no_show_frame�� 0���� �ʱ�ȭ
	}
}

bool FallenPerson::isAvailable() {
	return available;
}

void FallenPerson::setReported(bool b)
{
	this->emergency_reported = b;
}

bool FallenPerson::isReported()
{
	return emergency_reported;
}

bool FallenPerson::equalObj(bbox_t com) {
	if (this->box.track_id == com.track_id) {
		// Ʈ�� id�� ������, ���� �ڽ��� ���
		return true;
	}
	else {
		return false;

	}
}

//void FallenPerson::incrementFrame()
//{
//	this->insertedFrame++;
//}

bool FallenPerson::isExpired()
{
	if (++no_show_frame >= NO_SHOW_THRESHOLD) {
		return true;
	}
	return false;
}

FallingDetector::FallingDetector(int fps) {
	this->framerate = fps;
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

bool FallingDetector::areBoxesSame(bbox_t falling_obj, bbox_t fallen_obj, float threshold) {
	// �� �ڽ��� ��ġ�� ����ؼ�, threshold �̻� ��ġ�� ���� �ɷ� �Ǻ�

	// �� �ڽ��� ��ǥ ���
	unsigned int falling_obj_x1 = falling_obj.x;
	unsigned int falling_obj_x2 = falling_obj.x + falling_obj.w;
	unsigned int fallen_obj_x1 = fallen_obj.x;
	unsigned int fallen_obj_x2 = fallen_obj.x + fallen_obj.w;
	unsigned int falling_obj_y1 = falling_obj.y;
	unsigned int falling_obj_y2 = falling_obj.y + falling_obj.h;
	unsigned int fallen_obj_y1 = fallen_obj.y;
	unsigned int fallen_obj_y2 = fallen_obj.y + fallen_obj.h;

	unsigned int falling_obj_area = falling_obj.w * falling_obj.h;
	unsigned int fallen_obj_area = fallen_obj.w * fallen_obj.h;

	// SI = Max(0, Min(XA2, XB2) - Max(XA1, XB1)) * Max(0, Min(YA2, YB2) - Max(YA1, YB1))
	unsigned int overlapped_area = MAX(0, MIN(falling_obj_x2, fallen_obj_x2) - MAX(falling_obj_x1, fallen_obj_x1)) * MAX(0, MIN(falling_obj_y2, fallen_obj_y2) - MAX(falling_obj_y1, fallen_obj_y1));
	
	// get the area of the union
	unsigned int union_area = falling_obj_area + fallen_obj_area - overlapped_area;

	// get the portion of two areas
	float ratio = (float) overlapped_area / (float) union_area;
	/*std::cout << "falling: (" << falling_obj_x1 << "," << falling_obj_y1 << "), (" << falling_obj_x2 << ", " << falling_obj_y2 << ")" << std::endl;
	std::cout << "fallen: (" << fallen_obj_x1 << "," << fallen_obj_y1 << "), (" << fallen_obj_x2 << ", " << fallen_obj_y2 << ")" << std::endl;
	std::cout << "Calculated area ratio is: " << ratio << std::endl;*/
	if (ratio >= threshold) {
		return true;
	}
	else {
		return false;
	}
}

int FallingDetector::processDetectResult(std::vector<bbox_t>& result_vec, unsigned int frame_count) {
	int fallen_detected_code = 0;

	if (frame_count > currentFrameNo) { // �� �����Ӹ� ó����
		//std::cout << "processing a frame.." << std::endl;
		std::vector<bbox_t> new_falling_list = getBboxVector(result_vec, FALLING_PERSON);
		std::vector<bbox_t> new_fallen_list = getBboxVector(result_vec, FALLEN_PERSON);
		//std::cout << "falling_list's size: " << new_falling_list.size() << std::endl;
		//std::cout << "fallen_list's size: " << new_fallen_list.size() << std::endl;

		for (int i = 0; i < fallenPersonList.size(); i++) {
			// ������ fallenPersonList�� ���Ͽ�, ���� available�� false�� �ʱ�ȭ
			fallenPersonList.at(i).setAvailable(false);
		}

		for (int i = 0; i < new_fallen_list.size(); i++) { // �� fallenPerson object�鿡 ���Ͽ� �ϰ�ó��
			bool found_fallenperson_flag = false;
			FallenPerson* existing_person = NULL;
			// ���� ���� fallen person ��ü���� �˻�
			for (int j = 0; j < fallenPersonList.size(); j++) {
				if (fallenPersonList[j].equalObj(new_fallen_list[i])) {
					existing_person = &fallenPersonList[j]; // ã������ existing_person���� ����
					found_fallenperson_flag = true;
					// std::cout << "a new fallen person found: " << std::endl;
					break;
				}
			}

			if (!found_fallenperson_flag) {
				// �� ã�� (=���� ���� ��ü) -> ���� �������� falling_list���� ���� ���� �ִ��� �˻�
				bool inserted = false;
				//std::cout << "a new fallen person detected" <<  std::endl;
				
				// falling_list���� �Ļ��Ǿ����� �Ǵ��ϴ� ������, 1. �� falling_list���� ã���� �� ����, 2. ������ �ִ� falling_person�� ����� ��ġ & �ٿ������ ���� ��
				// 1. ���� ��ġ�� �� falling_list���� ã��
				for (int j = 0; j < new_falling_list.size(); j++) {
					if (areBoxesSame(new_falling_list[j], new_fallen_list[i], THRESHOLD_VALUE)) {
						// ã�������� - falling���� �Ļ��� ���� �ƴ� (=���������� �Ǻ�)
						FallenPerson added_abnormal = FallenPerson(new_fallen_list[i], frame_count, true);
						fallenPersonList.push_back(added_abnormal);
						fallen_detected_code = 2;
						inserted = true;
						break;
					}
				}

				// 2. ���� ��ġ�� ������ �ִ� falling_person���� ã��
				for (int j = 0; j < fallingPersonList.size() && !inserted; j++) {
					if (areBoxesSame(fallingPersonList[j], new_fallen_list[i], THRESHOLD_VALUE)) {
						// ã�������� - �� falling���� �Ļ��� ������ �Ǵ� (=�������� �Ǻ�)
						FallenPerson added_normal = FallenPerson(new_fallen_list[i], frame_count);
						fallenPersonList.push_back(added_normal);
						fallen_detected_code = 1;
						inserted = true;
					}
				}

				// 3. ���� ��찡 �ƴ� ���: ���ڱ� fallen_person�� ��Ÿ��. (=���������� �Ǻ�)
				if (!inserted) {
					FallenPerson added_abnormal = FallenPerson(new_fallen_list[i], frame_count, true);
					fallenPersonList.push_back(added_abnormal);
					fallen_detected_code = 2;
					inserted = true;
				}
			}
			else {
				// ã�� (=������ �ִ� ��ü) -> elapsedFrame�� 1 ������Ŵ
				// existing_person->incrementFrame();
				existing_person->setAvailable(true);
			}
		}

		// elapsedFrame�� �������� ���� (=�� �̻� ������ �ʴ�) ������Ʈ�� NO_SHOW_THRESHOLD�� ������ ����
		for (auto iter = fallenPersonList.begin(); iter != fallenPersonList.end(); iter++) {
			if (!iter->isAvailable()) {
				if (iter->isExpired()) {
					//dumpList();
					std::cout << "Track id " << iter->getBox().track_id << "�� �����. Elapsed time: " << iter->getElapsedTime(frame_count, framerate) << std::endl;
					fallenPersonList.erase(iter);
					iter--;
				}
			}
		}

		setCurrentFrameNo(frame_count);
		fallingPersonList = new_falling_list;
	}
	return fallen_detected_code;
}

bool FallingDetector::isEmergency() {
	for (int i = 0; i < fallenPersonList.size(); i++) {
		if (fallenPersonList[i].getElapsedTime(currentFrameNo, framerate) >= EMERGENCY_TIME_THRESHOLD) {
			if (!fallenPersonList[i].isReported()) {
				//std::cout << "Track id " << fallenPersonList[i].getBox().track_id << " reporting emergency" << std::endl;
				fallenPersonList[i].setReported(true);
				return true;
			}
		}
	}
	return false;
}

void FallingDetector::dumpList()
{
	std::cout << "*************** Dump of FallingDetector **************" << std::endl;
	std::cout << "fallingPersonList's size: " << fallingPersonList.size() << std::endl;
	std::cout << "fallenPersonList's size: " << fallenPersonList.size() << std::endl;
	std::cout << "currentFrameNo: " << currentFrameNo << std::endl << std:: endl;

	std::cout << "Contents of fallenPersonList: " << std::endl;
	for (int i = 0; i < fallenPersonList.size(); i++) {
		std::cout << "TrackID: " << fallenPersonList.at(i).getBox().track_id << std::endl;
	}
	std::cout << "*************** End of FallingDetector ***************" << std::endl;
	std::cout << std::endl;
}
