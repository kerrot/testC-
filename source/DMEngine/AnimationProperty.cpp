#include "AnimationProperty.h"
#include "AnimationDataPosition.h"
#include "AnimationDataSprite.h"
#include "AnimationDataEnable.h"


AnimationProperty::AnimationProperty(AnimationPropertyType type)
: _type(type) {
	AddKey(0);
}

AnimationProperty::~AnimationProperty() {
}

__int64 AnimationProperty::KeyMaxTime() {
	if (_keys.empty()) {
		return 0;
	}

	return _keys.rbegin()->first;
}

void AnimationProperty::Update(__int64 time, GameObjectPtr ptr) {
	if (_keys.empty()) {
		return;
	}

	AnimationDataPtr before, end;
	GetData(time, before, end);

	//interpolation. 
	before->Apply(time, ptr, end);
}

void AnimationProperty::GetData(__int64 time, AnimationDataPtr & before, AnimationDataPtr & after) {
	std::map<__int64, AnimationDataPtr>::iterator data = _keys.begin();
	std::map<__int64, AnimationDataPtr>::iterator iter = data;
	for (; iter != _keys.end(); ++iter) {
		if (iter->first > time) {
			break;
		}
		else {
			data = iter;
		}
	}

	before = data->second;
	after = (iter == _keys.end()) ? data->second : iter->second;
}

AnimationDataPtr AnimationProperty::AddKey(__int64 time) {
	std::map<__int64, AnimationDataPtr>::iterator iter = _keys.find(time);
	if (iter != _keys.end()) {
		return iter->second;
	}

	AnimationDataPtr tmp;
	switch (_type)
	{
	case ANIMATION_PROPERTY_POSITION:
		tmp = AnimationDataPositionPtr(new AnimationDataPosition(time));
		break;
	case ANIMATION_PROPERTY_SPRITE:
		tmp = AnimationDataSpritePtr(new AnimationDataSprite(time));
		break;
	case ANIMATION_PROPERTY_ENABLE:
		tmp = AnimationDataEnablePtr(new AnimationDataEnable(time));
		break;
	default:
		break;
	}

	if (tmp) {
		_keys[time] = tmp;
	}

	return tmp;
}

std::vector<AnimationDataPtr> AnimationProperty::AddPeroidKeys(__int64 period, int num) {
	static std::vector<AnimationDataPtr> empty;
	
	if (num > 0 && period > 0) {
		std::vector<AnimationDataPtr> data(num);	
		for (int i = 0; i < num; ++i) {
			data[i] = AddKey(period * i);
		}

		return data;
	}

	return empty;
}