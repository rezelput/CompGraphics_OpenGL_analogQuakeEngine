#include "object.h"

//прорисовка объекта
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
	// если ограничивающая сфера этого объекта сталкивается со сферой объекта
// и obj не является этим объектом
	if (((obj->position - position).Length() <= (obj->size + size)) &&
		(obj != ((CObject*)this)))
	{
		OnCollision(obj);		// выполнить столкновение этого объекта с obj

// проверка дочерних коллизий с obj
		if (HasChild())
			((CObject*)childNode)->ProcessCollisions(obj);

		// тест сестринских коллизий
		if (HasParent() && !IsLastChild())
			((CObject*)nextNode)->ProcessCollisions(obj);
	}

	// если у obj есть дочерние элементы, проверяем коллизии с этими дочерними элементами
	if (obj->HasChild())
		ProcessCollisions((CObject*)(obj->childNode));

	// если obj имеет сестринские связи, проверяем коллизии 
	if (obj->HasParent() && !obj->IsLastChild())
		ProcessCollisions((CObject*)(obj->nextNode));
}



void CObject::Prepare()
{
	OnPrepare();						//подготовитб объект

	if (HasChild())					// дочерние
		((CObject*)childNode)->Prepare();

	if (HasParent() && !IsLastChild())		// сестринские узлы
		((CObject*)nextNode)->Prepare();
}



CObject * CObject::FindRoot()
{
	// если у этого объекта есть родительский узел, вернуть корень
	if (parentNode)
		return ((CObject*)parentNode)->FindRoot();

	return this;
}

