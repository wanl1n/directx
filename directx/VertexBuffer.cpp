#include "VertexBuffer.h"
#include "RenderSystem.h"
#include "iostream"
#include <exception>

VertexBuffer::VertexBuffer(void* vertices, UINT vertexSize, UINT listSize, void* sbc, UINT bsSize, RenderSystem* system)
	: system(system), m_layout(0), m_buffer(0)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = vertexSize * listSize;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	m_size_vertex = vertexSize;
	m_size_list = listSize;

	if (FAILED(system->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		throw std::exception("VertexBuffer not created successfully");
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA ,0 },
		{"COLOR", 0,  DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};

	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(system->d3dDevice->CreateInputLayout(layout, size_layout, sbc, bsSize, &m_layout)))
	{
		throw std::exception("InputLayout not created successfully");
	}
}

VertexBuffer::VertexBuffer(std::vector<Vertex3D> vertices, UINT vertexSize, void* sbc, UINT bsSize, RenderSystem* system)
	: system(system), m_layout(0), m_buffer(0)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = vertexSize * vertices.size();
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices.data();

	this->m_size_vertex = vertexSize;
	this->m_size_list = vertices.size();

	if (FAILED(system->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		throw std::exception("VertexBuffer creation failed.");

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA ,0 },
		{"COLOR", 0,  DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};
	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(system->d3dDevice->CreateInputLayout(layout, size_layout, sbc, bsSize, &m_layout)))
		throw std::exception("InputLayout creation failed.");
}

VertexBuffer::VertexBuffer(std::vector<VertexMesh> vertices, void* sbc, UINT bsSize, RenderSystem* system)
	: system(system), m_layout(0), m_buffer(0) 
{
	UINT vertexSize = sizeof(VertexMesh);

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = vertexSize * vertices.size();
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices.data();

	this->m_size_vertex = vertexSize;
	this->m_size_list = vertices.size();

	if (FAILED(system->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		throw std::exception("VertexBuffer creation failed.");

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 },
		{ "NORMAL", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};
	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(system->d3dDevice->CreateInputLayout(layout, size_layout, sbc, bsSize, &m_layout)))
		throw std::exception("InputLayout creation failed.");
}

VertexBuffer::~VertexBuffer() 
{
	if (m_layout) m_layout->Release();
	if (m_buffer) m_buffer->Release();
}

UINT VertexBuffer::getSizeVertexList()
{
	return m_size_list;
}
