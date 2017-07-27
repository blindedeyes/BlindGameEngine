struct Vertex
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 uv : UV;
};

struct PixelShaderData
{
	float4 position : SV_POSITION;
};

PixelShaderData main(Vertex input)
{
	PixelShaderData result;
	
	result.position = input.position;

	return result;
}