using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Scripts.AI.DataStructures
{
    public class Cell
    {

        public Cell()
        {
            this.Left = 0;
            this.Right = 0;
            this.Top = 0;
            this.Bottom = 0;
            this.TicksSpentHere = 0;
        }

        /// <summary>
        /// Intialize the cell with proper data.
        /// </summary>
        /// <param name="top">Specifies the y-coordinate of the upper-left corner of a rectangle.</param>
        /// <param name="bottom">Specifies the y-coordinate of the lower-right corner of a rectangle.</param>
        /// <param name="left">Specifies the x-coordinate of the upper-left corner of a rectangle.</param>
        /// <param name="right">Specifies the x-coordinate of the lower-right corner of a rectangle.</param>
        public Cell(double top, double bottom, double left, double right, int id)
        {
            this.Left = left;
            this.Right = right;
            this.Top = top;
            this.Bottom = bottom;
            this.TicksSpentHere = 0;
            this.ID = id;
        }

        public void IncrementTicksSpentHere()
        {
            this.TicksSpentHere++;
        }

        public void Reset()
        {
            this.TicksSpentHere = 0;
        }

        /// <summary>
        /// Specifies the x-coordinate of the upper-left corner of a rectangle.
        /// </summary>
        public double Left
        {
            get; set;
        }

        /// <summary>
        /// Specifies the y-coordinate of the upper-left corner of a rectangle.
        /// </summary>
        public double Top
        {
            get; set;
        }

        /// <summary>
        /// Specifies the x-coordinate of the lower-right corner of a rectangle.
        /// </summary>
        public double Right
        {
            get; set;
        }

        /// <summary>
        /// Specifies the y-coordinate of the lower-right corner of a rectangle.
        /// </summary>
        public double Bottom
        {
            get; set;
        }

        public int TicksSpentHere
        {
            get; set;
        }

        public int ID;
    }
    /// <summary>
    /// A memory can be created using a simple data structure to represent the environment.
    /// The environment is broken down into a number of equally
    /// sized cells that are then stored in a List
    /// </summary>
    public class MemoryMapper
    {
        /// <summary>
        /// the 2d vector of memory cells
        /// </summary>
        public List<List<Cell>> cellsInMemoryMapper;
        Cell memoryMapperArea;

        public int NumberOfCellsX;
        public int NumberOfCellsY;
        int TotalCells;

        double individualCellSizeXAxis;
        double individualCellSizeYAxis;
        double totalAreaLengthOfXAxisInWorld;
        double totalAreaLengthOfYAxisInWorld;

        double previousPositionX = 0;
        double previousPositionY = 0;



        public MemoryMapper()
        {
            this.NumberOfCellsX = 0;
            this.NumberOfCellsY = 0;
            this.TotalCells = 0;
        }


        /// <summary>
        /// this must be called after an instance of this class has been
        /// created. This sets up all the cell coordinates.
        /// </summary>
        /// <param name="memoryAreaSize"></param>
        public void Init(Cell memoryAreaSize, int numberOfCellsX, int numberOfCellsY)
        {
            this.cellsInMemoryMapper = new List<List<Cell>>();
            this.memoryMapperArea = memoryAreaSize;
            this.NumberOfCellsX = numberOfCellsX;
            this.NumberOfCellsY = numberOfCellsY;
            this.TotalCells = this.NumberOfCellsX * this.NumberOfCellsY;

            totalAreaLengthOfXAxisInWorld = Mathf.Abs((float)this.memoryMapperArea.Left) + Mathf.Abs((float)this.memoryMapperArea.Right);
            totalAreaLengthOfYAxisInWorld = Mathf.Abs((float)this.memoryMapperArea.Top) + Mathf.Abs((float)this.memoryMapperArea.Bottom);

            individualCellSizeXAxis = totalAreaLengthOfXAxisInWorld / this.NumberOfCellsX;
            individualCellSizeYAxis = totalAreaLengthOfYAxisInWorld / this.NumberOfCellsY;

            var startPositionX = this.memoryMapperArea.Left;
            var startPositionY = this.memoryMapperArea.Top;
            int i = 0;
            for (int x = 0; x < this.NumberOfCellsY; ++x)
            {
                List<Cell> rowOfCells = new List<Cell>();
                for (int y = 0; y < this.NumberOfCellsX; ++y)
                {
                    rowOfCells.Add(new Cell(startPositionY, startPositionY - individualCellSizeYAxis, startPositionX, startPositionX + individualCellSizeXAxis, i));
                    startPositionX = startPositionX + individualCellSizeXAxis;
                    i++;

                }
                startPositionY = startPositionY - individualCellSizeYAxis;
                startPositionX = this.memoryMapperArea.Left;
                this.cellsInMemoryMapper.Add(rowOfCells);
            }
        }

        /// <summary>
        /// this method is called each frame and updates the time spent
        /// at the cell at this position
        /// </summary>
        /// <param name="xPos"></param>
        /// <param name="yPos"></param>
        public void Update(double xPos, double yPos)
        {
            // Make sure that the position is within a cell in the mapper.
            Cell cellInGivenPosition = this.GetCellInPosition(xPos, yPos);

            // TODO: Optimize this call away
            Cell cellInPreviousGivenPosition = this.GetCellInPosition(previousPositionX, previousPositionY);

            // Update the ticks only if the position is in a different cell otherwise we are in the same cell
            if ((cellInPreviousGivenPosition != null && cellInGivenPosition != null) && (cellInPreviousGivenPosition.ID != cellInGivenPosition.ID))
            {
                // If so then increment ticks spent in the cell
                if (cellInGivenPosition != null)
                    cellInGivenPosition.IncrementTicksSpentHere();

                this.previousPositionX = xPos;
                this.previousPositionY = yPos;
            }
            else
            {
                this.previousPositionX = xPos;
                this.previousPositionY = yPos;
            }
        }

        private Cell GetCellInPosition(double xPos, double yPos)
        {
            Cell cellInGivenPosition = null;
            foreach (List<Cell> cells in this.cellsInMemoryMapper)
            {
                foreach(Cell cell in cells)
                {
                    if((xPos >= cell.Left) && (xPos <= cell.Right) && (yPos <= cell.Top) && (yPos >= cell.Bottom))
                    {
                        cellInGivenPosition = cell;
                        break;
                    }
                }

                if (cellInGivenPosition != null)
                    break;
            }

            return cellInGivenPosition;
        }

        /// <summary>
        /// returns how many ticks have been spent at this cell position
        /// </summary>
        /// <param name="xPos"></param>
        /// <param name="yPos"></param>
        /// <returns></returns>
        public int TicksLingered(double xPos, double yPos)
        {
            // Make sure that the position is within a cell in the mapper.
            var cellInGivenPosition = this.GetCellInPosition(xPos, yPos);

            // If so then return the ticks spent if there are any
            if (cellInGivenPosition != null && cellInGivenPosition.TicksSpentHere > 0)
                return cellInGivenPosition.TicksSpentHere;

            return 0;
        }
        /// <summary>
        /// returns the total number of cells visited
        /// </summary>
        /// <returns></returns>
        public int NumCellsVisited()
        {
            int numberOfCellsVisited = 0;
            foreach (List<Cell> cells in this.cellsInMemoryMapper)
            {
                foreach (Cell cell in cells)
                {
                    if (cell.TicksSpentHere > 0)
                        numberOfCellsVisited++;
                }
            }

            return numberOfCellsVisited;
        }

        /// <summary>
        /// returns if the cell at the given position has been visited or not
        /// </summary>
        /// <param name="xPos"></param>
        /// <param name="yPos"></param>
        /// <returns></returns>
        public bool BeenVisited(double xPos, double yPos)
        {
            // Make sure that the position is within a cell in the mapper.
            var cellInGivenPosition = this.GetCellInPosition(xPos, yPos);

            // If so then return true if time was spent in the cell
            if (cellInGivenPosition != null && cellInGivenPosition.TicksSpentHere > 0)
                return true;

            return false;
        }

        ///// <summary>
        ///// This method renders any visited cells in shades of red. The
        ///// darker the red, the more time has been spent at that cell
        ///// </summary>
        ///// <param name="surface"></param>
        //public void Render(HDC surface)
        //{

        //}

        public void Reset()
        {
            this.cellsInMemoryMapper.Clear();
            this.individualCellSizeXAxis = 0;
            this.individualCellSizeYAxis = 0;
            this.memoryMapperArea = new Cell();
            this.NumberOfCellsX = 0;
            this.NumberOfCellsY = 0;
            this.totalAreaLengthOfXAxisInWorld = 0;
            this.totalAreaLengthOfYAxisInWorld = 0;
            this.TotalCells = 0;

            foreach (List<Cell> cells in this.cellsInMemoryMapper)
            {
                foreach (Cell cell in cells)
                {
                    cell.TicksSpentHere = 0;
                }
            }
        }
        public int NumCells() { return TotalCells; }
    }
}
