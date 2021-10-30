#pragma once
#include "framework.h"
#include <iostream>
#include <Serializer.h>
#include <Deserializer.h>

class NetworkObject {
public:

	NetworkObject(ClassID classID) : m_classID(classID) {};
	NetworkObject() = default;
	~NetworkObject() = default;

	virtual void Print() = 0;
	virtual void Write(Serializer * s) = 0;
	virtual void Read(Deserializer* d) = 0;

	ClassID m_classID;
};