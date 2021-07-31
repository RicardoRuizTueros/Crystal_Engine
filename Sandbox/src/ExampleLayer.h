#pragma once

#include "Crystal.h"

using namespace Crystal;

class ExampleLayer : public Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Event& event) override;

private:
	OrthographicCameraController cameraController;

	Reference<Shader> logoTextureShader;
	Reference<VertexArray> logoTextureVertexArray;
	Reference<Texture2D> logoTexture;

	Reference<Shader> checkerTextureShader;
	Reference<VertexArray> checkerTextureVertexArray;
	Reference<Texture2D> checkerTexture;

	Reference<Shader> squareShader;
	Reference<VertexArray> squareVertexArray;
	vec3 squareShaderColor = { 0.2f, 0.3f, 0.8f };
};
