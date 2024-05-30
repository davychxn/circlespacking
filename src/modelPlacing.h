// An equal-circles packing algorithm
// Used to add new circles to existing placed circles
// For instance to add new models to a scene already having other models
// Developer: Davy Chen
// https://www.linkedin.com/in/davychxn/
// May 30th, 2024
// BSD 2 Clause License

#ifndef MODELPLACING_H
#define MODELPLACING_H

#include <QVector2D>
#include <vector>
#include "../renderer/RenderModel.h"

#define SWT_MODEL_MINIMAL_DISTANCE 10.0f

typedef struct _ModelBoundingCircle
{
    QVector2D center;
    float radius;
}ModelBoundingCircle;

class ModelPlacing
{
public:
    ModelPlacing();
    ~ModelPlacing();

public:
    void addBoundingCircle(QVector2D center, float radius);
    void clearBoundingCircles();
    QVector2D placeModel(std::vector<RenderModel*>& models, float radius);
    bool circlesIntersection(QVector2D center1, float radius1, QVector2D center2, float radius2, QVector2D& intersection1, QVector2D& intersection2);

private:
    void updateModelBoundingCircles(std::vector<RenderModel*>& models);

private:
    std::vector<ModelBoundingCircle> v_circles;
};

#endif // MODELPLACING_H
