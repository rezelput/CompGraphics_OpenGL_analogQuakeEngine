#include "object.h"

//���������� �������
void CObject::Draw(CCamera *camera) 
{
	// push modelview matrix on stack
	glPushMatrix();
		OnDraw(camera);		// draw this object
		if (HasChild())		// draw children
			((CObject*)childNode)->Draw(camera);
	glPopMatrix();

	// draw siblings
	if (HasParent() && !IsLastChild())
		((CObject*)nextNode)->Draw(camera);
}



void CObject::Animate(scalar_t deltaTime) 
{
	OnAnimate(deltaTime);		// animate this object

	// animate children
	if (HasChild())
		((CObject*)childNode)->Animate(deltaTime);

	// animate siblings
	if (HasParent() && !IsLastChild())
		((CObject*)nextNode)->Animate(deltaTime);

	if (isDead)
		delete this;
}


void CObject::ProcessCollisions(CObject *obj) 
{
	// ���� �������������� ����� ����� ������� ������������ �� ������ �������
// � obj �� �������� ���� ��������
	if (((obj->position - position).Length() <= (obj->size + size)) &&
		(obj != ((CObject*)this)))
	{
		OnCollision(obj);		// ��������� ������������ ����� ������� � obj

// �������� �������� �������� � obj
		if (HasChild())
			((CObject*)childNode)->ProcessCollisions(obj);

		// ���� ����������� ��������
		if (HasParent() && !IsLastChild())
			((CObject*)nextNode)->ProcessCollisions(obj);
	}

	// ���� � obj ���� �������� ��������, ��������� �������� � ����� ��������� ����������
	if (obj->HasChild())
		ProcessCollisions((CObject*)(obj->childNode));

	// ���� obj ����� ����������� �����, ��������� �������� 
	if (obj->HasParent() && !obj->IsLastChild())
		ProcessCollisions((CObject*)(obj->nextNode));
}



void CObject::Prepare()
{
	OnPrepare();						//����������� ������

	if (HasChild())					// ��������
		((CObject*)childNode)->Prepare();

	if (HasParent() && !IsLastChild())		// ����������� ����
		((CObject*)nextNode)->Prepare();
}



CObject * CObject::FindRoot()
{
	// ���� � ����� ������� ���� ������������ ����, ������� ������
	if (parentNode)
		return ((CObject*)parentNode)->FindRoot();

	return this;
}

