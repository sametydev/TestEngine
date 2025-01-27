#pragma once

#include <SlateEngine/Engine/Graphics/Buffer/DXVertexBuffer.h>
#include <SlateEngine/Engine/Graphics/Buffer/DXIndexBuffer.h>
#include <SlateEngine/Engine/Graphics/Buffer/DXConstantBuffer.h>

class ENGINE_API BufferCache {
public:
	//TODO: Dont store data twice, we are storing buffer's data twice on memory but its better than storing 100x times xD
	//		Fixing: Implement UUID or UID system for define buffers.

	static std::map<void*, std::shared_ptr<DXVertexBuffer>> mVertexBuffers;
	static std::map<void*, std::shared_ptr<DXIndexBuffer>> mIndexBuffers;

	[[nodiscard]] inline static DXVertexBuffer* CreateVertexBuffer(VertexBufferDesc desc) {
		std::shared_ptr<DXVertexBuffer> buffer = nullptr;

		auto found = mVertexBuffers.find(&desc.pData);
		if (found != mVertexBuffers.end()) {
			return found->second.get();
		}

		buffer = std::make_shared<DXVertexBuffer>();
		buffer->Create(desc);
		mVertexBuffers.insert(std::make_pair(&desc.pData, buffer));

		return buffer.get();
	}

	[[nodiscard]] inline static DXIndexBuffer* CreateIndexBuffer(IndexBufferDesc desc) {
		std::shared_ptr<DXIndexBuffer> buffer = nullptr;

		auto found = mIndexBuffers.find(&desc.pData);
		if (found != mIndexBuffers.end()) {
			return found->second.get();
		}

		buffer = std::make_shared<DXIndexBuffer>();
		buffer->Create(desc);
		mIndexBuffers.insert(std::make_pair(&desc.pData, buffer));

		return buffer.get();
	}

};