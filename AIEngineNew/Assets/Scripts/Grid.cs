using UnityEngine;
using Assets.Scripts.AI.DataStructures;

[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class Grid : MonoBehaviour
{

    public int xSize, ySize;

    private Mesh mesh;
    private Vector3[] vertices;
    public MemoryMapper Mapper;

    private void Awake()
    {
        //Generate();
    }

    private void GenerateGrid()
    {
        if (this.Mapper != null)
        {
            vertices = new Vector3[(this.Mapper.NumberOfCellsX + 1) * (this.Mapper.NumberOfCellsY + 1)];

            Vector2[] uv = new Vector2[vertices.Length];
            Vector4[] tangents = new Vector4[vertices.Length];
            Vector4 tangent = new Vector4(1f, 0f, 0f, -1f);
            Color32[] colors = new Color32[vertices.Length];

            int i = 0;

            int y = 0;
            int x = 0;
            for (y = 0; y < this.Mapper.NumberOfCellsY; y++)
            {
                x = 0;
                for (; x < this.Mapper.NumberOfCellsX; x++)
                {

                    vertices[i] = new Vector3((float)this.Mapper.cellsInMemoryMapper[y][x].Top, (float)this.Mapper.cellsInMemoryMapper[y][x].Left);
                    uv[i] = new Vector2((float)this.Mapper.cellsInMemoryMapper[y][x].Top / this.Mapper.NumberOfCellsX, (float)this.Mapper.cellsInMemoryMapper[y][x].Left / this.Mapper.NumberOfCellsY);
                    tangents[i] = tangent;
                    colors[i] = new Color(1 - RandomProvider.Map(this.Mapper.TicksLingered(this.Mapper.cellsInMemoryMapper[y][x].Top / 2, this.Mapper.cellsInMemoryMapper[y][x].Left / 2), 0, 255, 0, 1), 1, 1);
                    i++;

                }
                x--;
                vertices[i] = new Vector3((float)this.Mapper.cellsInMemoryMapper[y][x].Top, (float)this.Mapper.cellsInMemoryMapper[y][x].Right);
                uv[i] = new Vector2((float)this.Mapper.cellsInMemoryMapper[y][x].Top / this.Mapper.NumberOfCellsX, (float)this.Mapper.cellsInMemoryMapper[y][x].Right / this.Mapper.NumberOfCellsY);
                tangents[i] = tangent;
                colors[i] = new Color(1 - RandomProvider.Map(this.Mapper.TicksLingered(this.Mapper.cellsInMemoryMapper[y][x].Top / 2, this.Mapper.cellsInMemoryMapper[y][x].Right / 2), 0, 255, 0, 1), 1, 1);
                i++;

            }
            y--;
            for (x = 0; x < this.Mapper.NumberOfCellsX; x++)
            {
                vertices[i] = new Vector3((float)this.Mapper.cellsInMemoryMapper[y][x].Bottom, (float)this.Mapper.cellsInMemoryMapper[y][x].Left);
                uv[i] = new Vector2((float)this.Mapper.cellsInMemoryMapper[y][x].Bottom / this.Mapper.NumberOfCellsX, (float)this.Mapper.cellsInMemoryMapper[y][x].Left / this.Mapper.NumberOfCellsY);
                tangents[i] = tangent;
                colors[i] = new Color(1 - RandomProvider.Map(this.Mapper.TicksLingered(this.Mapper.cellsInMemoryMapper[y][x].Bottom / 2, this.Mapper.cellsInMemoryMapper[y][x].Left / 2), 0, 255, 0, 1), 1, 1);
                i++;
            }
            x--;
            vertices[i] = new Vector3((float)this.Mapper.cellsInMemoryMapper[y][x].Bottom, (float)this.Mapper.cellsInMemoryMapper[y][x].Right);
            uv[i] = new Vector2((float)this.Mapper.cellsInMemoryMapper[y][x].Bottom / this.Mapper.NumberOfCellsX, (float)this.Mapper.cellsInMemoryMapper[y][x].Right / this.Mapper.NumberOfCellsY);
            tangents[i] = tangent;
            colors[i] = new Color(1 - RandomProvider.Map(this.Mapper.TicksLingered(this.Mapper.cellsInMemoryMapper[y][x].Bottom / 2, this.Mapper.cellsInMemoryMapper[y][x].Right / 2), 0, 255, 0, 1), 1, 1);
            i++;


            mesh.vertices = vertices;
            mesh.uv = uv;
            mesh.tangents = tangents;

            int[] triangles = new int[this.Mapper.NumberOfCellsX * this.Mapper.NumberOfCellsY * 6];
            for (int ti = 0, vi = 0, h = 0; h < this.Mapper.NumberOfCellsY; h++, vi++)
            {
                for (int t = 0; t < this.Mapper.NumberOfCellsX; t++, ti += 6, vi++)
                {
                    triangles[ti] = vi;
                    triangles[ti + 3] = triangles[ti + 2] = vi + 1;
                    triangles[ti + 4] = triangles[ti + 1] = vi + this.Mapper.NumberOfCellsX + 1;
                    triangles[ti + 5] = vi + this.Mapper.NumberOfCellsX + 2;
                }
            }

            mesh.colors32 = colors;
            mesh.triangles = triangles;

            mesh.RecalculateNormals();
        }
    }
    // TODO MOVEMENT GRID FOR THE SWeePERS
    public void Generate()
    {
        if(this.mesh == null)
            GetComponent<MeshFilter>().mesh = mesh = new Mesh();
        mesh.name = "Procedural Grid";

        if(this.Mapper != null)
        {
            if(mesh.vertices.Length != ((this.Mapper.NumberOfCellsX + 1) * (this.Mapper.NumberOfCellsY + 1)))
            {
                this.GenerateGrid();
            } else if (mesh.vertices.Length == ((this.Mapper.NumberOfCellsX + 1) * (this.Mapper.NumberOfCellsY + 1)))
            {
                Color32[] colors = new Color32[vertices.Length];
                for (int vc = 0; vc < mesh.vertices.Length; ++vc)
                {
                    colors[vc] = new Color32(255,255,255,255);
                }

                int i = 0;

                int y = 0;
                int x = 0;
                for (y = 0; y < this.Mapper.NumberOfCellsY; y++)
                {
                    x = 0;
                    for (; x < this.Mapper.NumberOfCellsX; x++)
                    {
                        colors[i] = new Color(1 - RandomProvider.Map(this.Mapper.TicksLingered(this.Mapper.cellsInMemoryMapper[y][x].Top / 2, this.Mapper.cellsInMemoryMapper[y][x].Left / 2), 0, 255, 0, 1), 1, 1);
                        i++;
                    }
                    x--;
                    colors[i] = new Color(1 - RandomProvider.Map(this.Mapper.TicksLingered(this.Mapper.cellsInMemoryMapper[y][x].Top / 2, this.Mapper.cellsInMemoryMapper[y][x].Right / 2), 0, 255, 0, 1), 1, 1);
                    i++;
                }
                y--;
                for (x = 0; x < this.Mapper.NumberOfCellsX; x++)
                {
                    colors[i] = new Color(1 - RandomProvider.Map(this.Mapper.TicksLingered(this.Mapper.cellsInMemoryMapper[y][x].Bottom / 2, this.Mapper.cellsInMemoryMapper[y][x].Left / 2), 0, 255, 0, 1), 1, 1);
                    i++;
                }
                x--;
                colors[i] = new Color(1 - RandomProvider.Map(this.Mapper.TicksLingered(this.Mapper.cellsInMemoryMapper[y][x].Bottom / 2, this.Mapper.cellsInMemoryMapper[y][x].Right / 2), 0, 255, 0, 1), 1, 1);
                i++;

                mesh.colors32 = colors;
                mesh.RecalculateNormals();
            }
        }

        
    }

    private void OnDrawGizmos()
    {
        
    }
}