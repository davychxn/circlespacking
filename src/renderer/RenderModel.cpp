#include "./RenderModel.h"

RenderModel::RenderModel()
{
    position = QVector3D(0.0f, 0.0f, 0.0f);
}

RenderModel::~RenderModel()
{

}

void RenderModel::setMesh(QVector3D pos, float radius2D)
{
    position = pos;
    m_radius2D = radius2D;
}

QVector3D RenderModel::getPosition() const
{
    return position;
}

float RenderModel::getRadius2D() const
{
    return m_radius2D;
}
