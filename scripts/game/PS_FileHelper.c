class PS_FileHelper
{
	static void WriteVector(FileHandle fileHandle, vector v)
	{
		float x, y, z;
		x = v[0];
		y = v[1];
		z = v[2];
		fileHandle.Write(x, 4);
		fileHandle.Write(y, 4);
		fileHandle.Write(z, 4);
	}
	
	static vector ReadVector(FileHandle fileHandle)
	{
		float x, y, z;
		fileHandle.Read(x, 4);
		fileHandle.Read(y, 4);
		fileHandle.Read(z, 4);
		return Vector(x, y, z);
	}
	
	static void WriteStaticArray(FileHandle fileHandle, int[] arr, int length, int size)
	{
		for (; length > 0; length--)
			fileHandle.Write(arr[length - 1], size);
	}
	
	static void ReadStaticArray(FileHandle fileHandle, int[] arr, int length, int size)
	{
		for (; length > 0; length--)
		{
			int data;
			fileHandle.Read(data, size);
			arr[length - 1] = data;
		}
	}
}