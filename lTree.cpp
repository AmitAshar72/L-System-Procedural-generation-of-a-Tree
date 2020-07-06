#include "lTree.h"



lTree::lTree()
{

	angle = (22.5f * XM_PI)/180;
	m_worldMatrix = XMMatrixIdentity();
	
}


lTree::~lTree()
{
}

bool lTree::Initialise(ID3D11Device * device, bool keyDown)
{
	if (keyDown)
	{
		D3D11_BUFFER_DESC vBufferDesc;
		D3D11_BUFFER_DESC iBufferDesc;

		D3D11_SUBRESOURCE_DATA vData;
		D3D11_SUBRESOURCE_DATA iData;

		HRESULT result;

		vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vBufferDesc.ByteWidth = sizeof(VertexType) * m_vertices.size();
		vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vBufferDesc.CPUAccessFlags = 0;
		vBufferDesc.MiscFlags = 0;
		vBufferDesc.StructureByteStride = 0;

		vData.pSysMem = m_vertices.data();
		vData.SysMemPitch = 0;
		vData.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&vBufferDesc, &vData, &m_vBuffer);
		if (FAILED(result))
			return false;

		iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		iBufferDesc.ByteWidth = sizeof(int) * m_indices.size();
		iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		iBufferDesc.CPUAccessFlags = 0;
		iBufferDesc.MiscFlags = 0;
		iBufferDesc.StructureByteStride = 0;

		iData.pSysMem = m_indices.data();
		iData.SysMemPitch = 0;
		iData.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&iBufferDesc, &iData, &m_iBuffer);
		if (FAILED(result))
			return false;
	
	}
	return true;
}


bool lTree::Render(ID3D11DeviceContext * context)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 1, &m_vBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(m_iBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	return true;
}

void lTree::interpretRule(std::string rule, float posX, float posY, float posZ)
{
	
	/*turtleStack.empty();
	indexStack.empty();*/
	size = rule.length();	
	currentState.pos = XMVectorSet(posX, posY, posZ , 1.0f);
	currentState.rotation = XMMatrixIdentity();
	
	XMMATRIX rotMatrix = XMMatrixIdentity();
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		nextState = currentState;
		XMVECTOR rotated = XMVector3Transform(currentState.dir, rotMatrix);
		switch (rule.at(i))
		{
			case 'F':
			{	nextState.pos += rotated;
				XMFLOAT3 vertPos;
				XMStoreFloat3(&vertPos, currentState.pos);
				m_vertices.push_back(vertPos);
				XMStoreFloat3(&vertPos, nextState.pos);
				m_vertices.push_back(vertPos);
				m_indices.push_back(index);
				index = m_indices.size();
				m_indices.push_back(index);
			break;
			}
			case 'f':
			{
				nextState.pos +=  rotated;
				index = m_indices.size(); 
			break;
			}
			case '+':
			{	
				rotMatrix *= XMMatrixRotationAxis(rotMatrix.r[2], angle);
				//rotMatrix *= XMMatrixRotationZ(angle);
			break;
			}
			case '-':
			{	
				rotMatrix *= XMMatrixRotationAxis(rotMatrix.r[2], -angle);
				//rotMatrix *= XMMatrixRotationZ(-angle);
			break;
			}
			case '&':
			{
				rotMatrix *= XMMatrixRotationAxis(rotMatrix.r[0], angle);
			break;
			}
			case '^':
			{
				rotMatrix *= XMMatrixRotationAxis(rotMatrix.r[0], -angle);
			break;
			}
			case'\\':
			{
				rotMatrix *= XMMatrixRotationAxis(rotMatrix.r[1], angle);
			break;
			}
			case '/':
			{
				rotMatrix *= XMMatrixRotationAxis(rotMatrix.r[1], -angle);
				break;
			}
			case '|':
			{
				rotMatrix *= XMMatrixRotationAxis(rotMatrix.r[2], (180.0f * XM_PI) / 180);
				break;
			}
			case '[':
			{
				currentState.rotation = rotMatrix;
				turtleStack.push(currentState);
				indexStack.push(index);
				break;
			}	
			case ']':
			{
				nextState = turtleStack.top();
				rotMatrix = nextState.rotation;
				turtleStack.pop();
				index = indexStack.top();
				indexStack.pop();
				break;
			}
			default:
				break;
		}
		currentState = nextState;
	}
}

void lTree::SetWorldMatrix(XMMATRIX world)
{
	m_worldMatrix = world;
}

XMMATRIX lTree::GetWorldMatrix()
{
	return m_worldMatrix;
}

int lTree::GetIndexCount()
{
	return m_indices.size();
}
