# Circles Packing Algorithm

Self-invented algorithm to pack equal-circles one by one.

Used to add new circles to existing placed circles.

For instance to add new models to a scene already having other models.

(https://github.com/davychxn/circlespacking/blob/main/resources/screenshot1.jpg)



Used QT QVector2D libraries to do 3D/2D math.

# Usage:

```cpp

// A series of models' bounding circles
float radius [] = {10.0f, 12.0f, 15.0f, 18.0f, 21.0f};
std::vector<RenderModel*> v_models;
ModelPlacing modelPlacing;

for (int i = 0; i < sizeof(radius) / sizeof(float); i++)
{
	QVector2D position = modelPlacing.placeModel(v_models, radius[i]);
	RenderModel* renderModel = new RenderModel;
	renderModel->setMesh(QVector3D(position.x(), 0.0f, position.y()), radius[i]);
	v_models.push_back(renderModel);
}

```

Davy Chen

May 30th, 2024

BSD 2 Clause License
