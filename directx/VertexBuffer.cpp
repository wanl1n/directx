#include "VertexBuffer.h"
#include "RenderSystem.h"
#include "iostream"

VertexBuffer::VertexBuffer(RenderSystem* system) : system(system), m_layout(0), m_buffer(0) {}
VertexBuffer::~VertexBuffer() {}

// 2D Quad
bool VertexBuffer::loadQuad(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	if (m_layout) m_layout->Release();
	if (m_buffer) m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;

	if (FAILED(system->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		// Semantic Name, Semantic Index, Format, Input Slot, Aligned Byte Offset, Input Slot Class, Instance Data
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(system->d3dDevice->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
		return false;
	
	return true;
}

bool VertexBuffer::loadCircle(std::vector<CircleVertex> list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	if (m_layout) m_layout->Release();
	if (m_buffer) m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices.data();

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;

	if (FAILED(system->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		// Semantic Name, Semantic Index, Format, Input Slot, Aligned Byte Offset, Input Slot Class, Instance Data
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(system->d3dDevice->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
		return false;

	return true;
}

// 3D Cube
bool VertexBuffer::loadIndexed(std::vector<Vertex3D> vertices, UINT size_vertex, void* shader_byte_code, UINT size_byte_shader)
{
	if (m_layout) m_layout->Release();
	if (m_buffer) m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * vertices.size();
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices.data();

	this->m_size_vertex = size_vertex;
	this->m_size_list = vertices.size();

	if (FAILED(system->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		// Semantic Name, Semantic Index, Format, Input Slot, Aligned Byte Offset, Input Slot Class, Instance Data
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(system->d3dDevice->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
		return false;

	return true;
}

bool VertexBuffer::loadTool(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	if (m_layout) m_layout->Release();
	if (m_buffer) m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;

	if (FAILED(system->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		// Semantic Name, Semantic Index, Format, Input Slot, Aligned Byte Offset, Input Slot Class, Instance Data
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(system->d3dDevice->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
		return false;

	return true;
}

bool VertexBuffer::release()
{
	if (m_layout) m_layout->Release();
	if (m_buffer) m_buffer->Release();
	delete this;
	return true;
}

UINT VertexBuffer::getSizeVertexList()
{
	return m_size_list;
}
