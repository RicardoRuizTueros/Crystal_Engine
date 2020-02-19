#pragma once

#include "Crystal.h"

namespace Crystal 
{
	class Sandbox2D : public Layer
	{

	public:
		Sandbox2D();
		virtual ~Sandbox2D() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep timestep) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	private:
		OrthographicCameraController cameraController;

		Reference<Texture2D> checkerTexture;

		// To do: Remove this!
		Reference<VertexArray> squareVertexArray;
		Reference<Shader> flatColorShader;

		vec4 squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};
}