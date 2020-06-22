#pragma once

#include "Crystal.h"

namespace Crystal
{
	class EditorLayer : public Layer
	{

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep timestep) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	private:
		OrthographicCameraController cameraController;
		vec2 viewportSize = { 0.0f, 0.0f };

		// To do: Remove this!
		Reference<VertexArray> squareVertexArray;
		Reference<Shader> flatColorShader;
		Reference<Texture2D> checkerTexture;
		Reference<FrameBuffer> frameBuffer;

		vec4 squareColor;
	};
}