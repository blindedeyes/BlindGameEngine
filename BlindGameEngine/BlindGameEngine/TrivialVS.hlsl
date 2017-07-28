struct Vertex
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 uv : UV;
};

cbuffer WorldViewProj
{
	float4x4 view;
	float4x4 proj;
	float4x4 worldMatrix;
};

struct PixelShaderData
{
	float4 position : SV_POSITION;
};

PixelShaderData main(Vertex input)
{
	PixelShaderData result;
	
	result.position = input.position;

	result.position = mul(result.position, worldMatrix);
	result.position = mul(result.position, view);
	result.position = mul(result.position, proj);


	return result;
}