#include "modelPlacing.h"

ModelPlacing::ModelPlacing()
{

}

ModelPlacing::~ModelPlacing()
{

}

void ModelPlacing::addBoundingCircle(QVector2D center, float radius)
{
    ModelBoundingCircle circle;
    circle.center = center;
    circle.radius = radius;
    v_circles.push_back(circle);
}

void ModelPlacing::clearBoundingCircles()
{
    v_circles.clear();
}

// If existing models' positions are modified, we need to consider
void ModelPlacing::updateModelBoundingCircles(std::vector<RenderModel*>& models)
{
    clearBoundingCircles();

    for (auto model: models)
    {
        QVector3D position = model->getPosition();
        QVector2D pos(position.x(), position.z());

        addBoundingCircle(pos, model->getRadius2D());
    }
}

// Use it to get placing position of a new model
QVector2D ModelPlacing::placeModel(std::vector<RenderModel*>& models, float radius)
{
    // Update positions of bounding circles of existing models
    updateModelBoundingCircles(models);

    // Where to place new model
    QVector2D modelPlacing(0.0f, 0.0f);
    float minimumDistanceFactor = 0.0f;
    bool distanceFactorUpdated = false;

    for (auto circle: v_circles)
    {
        QVector2D v1, v2;
        QVector2D center1 = QVector2D(circle.center.x(), circle.center.y() + circle.radius + radius);
        circlesIntersection(circle.center, circle.radius + radius, center1, SWT_MODEL_MINIMAL_DISTANCE, v1, v2);

        // Calculate a few places we can place new model neighbouring existing models
        QVector2D v3 = center1.normalized();
        QVector2D v4 = v2.normalized();
        float differ = QVector2D::dotProduct(v3, v4);
        float radian = acos(differ);

        int placingPointCount = SWT_PI * 2.0f / radian;

        for (int i = 0; i < placingPointCount; i++)
        {
            float f1 = radian * i;
            float f2 = circle.radius + radius;
            float x1 = cos(f1) * f2;
            float y1 = sin(f1) * f2;

            QVector2D placingPoint = QVector2D(circle.center.x() + x1, circle.center.y() + y1);
            float distanceFactor = placingPoint.length();
            bool placeable = true;
            // Check if unplaceable
            for (auto circle1: v_circles)
            {
                QVector2D v5 = placingPoint - circle1.center;
                if (v5.length() < (circle1.radius + radius))
                {
                    // Intersect with this circle, this point unavailable
                    placeable = false;
                    break;
                }
            }

            if (!placeable)
            {
                continue;
            }

            // Get best model placing point
            if (!distanceFactorUpdated)
            {
                modelPlacing = placingPoint;
                minimumDistanceFactor = distanceFactor;
                distanceFactorUpdated = true;
            }
            else
            {
                if (distanceFactor < minimumDistanceFactor)
                {
                    modelPlacing = placingPoint;
                    minimumDistanceFactor = distanceFactor;
                }
            }
        }
    }

    addBoundingCircle(modelPlacing, radius);
    return modelPlacing;
}

// Get intersections of 2 circles
bool ModelPlacing::circlesIntersection(QVector2D center1, float radius1, QVector2D center2, float radius2, QVector2D& intersection1, QVector2D& intersection2)
{
    QVector2D v1 = center1 - center2;
    float d = v1.length();

    if (d > radius1 + radius2) return false;
    if (d + radius1 < radius2) return false;
    if (d + radius2 < radius1) return false;

    float a = (radius1 * radius1 - radius2 * radius2 + d * d) / (2 * d);

    float h = sqrt(radius1 * radius1 - a * a);

    QVector2D v2 = (center2 - center1);
    v2 = (v2 * (a / d));
    v2 = (v2 + center1);

    float x3, y3, x4, y4 = 0;

    x3 = v2.x() + h * (center2.y() - center1.y()) / d;
    y3 = v2.y() - h * (center2.x() - center1.x()) / d;

    x4 = v2.x() - h * (center2.y() - center1.y()) / d;
    y4 = v2.y() + h * (center2.x() - center1.x()) / d; ;

    //out parameters for a line renderer
    intersection1 = QVector2D(x3, y3);
    intersection2 = QVector2D(x4, y4);

    return true;
}
