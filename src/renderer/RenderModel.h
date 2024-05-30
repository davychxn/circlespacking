// A Class holding data of a model
// Developer: Davy Chen
// https://www.linkedin.com/in/davychxn/
// May 30th, 2024
// BSD 2 Clause License

#ifndef RENDERMODEL_H
#define RENDERMODEL_H

class RenderModel
{
public:
    RenderModel();
    virtual ~RenderModel();

public:
    void setMesh(QVector3D pos, float radius2D);
    QVector3D getPosition() const;
    float getRadius2D() const;

private:
	// Model position
    QVector3D position;
	// Model bounding circle's radius on X-Z plane
    float m_radius2D = 0.0f;

};

#endif // RENDERMODEL_H
