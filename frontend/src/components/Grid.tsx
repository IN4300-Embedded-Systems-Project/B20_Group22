import { useState, useEffect, useRef } from "react";
import { Button } from "@/components/ui/button";

const CELL_SIZE = 40; // Each cell is 40px × 40px
const GRID_WIDTH = 30; // Number of columns
const GRID_HEIGHT = 14; // Number of rows

interface Point {
  x: number;
  y: number;
}

function convertPathToInstructions(path: Point[]): string {
  if (path.length < 2) return "";
  const directions = ["N", "E", "S", "W"];
  let currentDirIdx = 0; // initial facing North
  let result = "";
  let steps = 0;
  let currentSeg: string | null = null;

  const getDir = (dx: number, dy: number): string => {
    if (dx === 0 && dy === 1) return "S";
    if (dx === 0 && dy === -1) return "N";
    if (dx === 1 && dy === 0) return "E";
    if (dx === -1 && dy === 0) return "W";
    throw new Error("Invalid move");
  };

  for (let i = 1; i < path.length; i++) {
    const dx = path[i].x - path[i - 1].x;
    const dy = path[i].y - path[i - 1].y;
    const seg = getDir(dx, dy);
    if (currentSeg !== seg) {
      if (steps) {
        result += `F${steps}`;
        steps = 0;
      }
      const targetIdx = directions.indexOf(seg);
      let diff = (targetIdx - currentDirIdx + 4) % 4;
      if (diff === 3) result += "L";
      else if (diff === 2) result += "RR";
      else if (diff === 1) result += "R";
      currentDirIdx = targetIdx;
      currentSeg = seg;
    }
    steps++;
  }
  if (steps) result += `F${steps}`;
  return result;
}

export default function Grid() {
  const [path, setPath] = useState<Point[]>([]);
  const lastValidPoint = useRef<Point | null>(null);
  const [isSelecting, setIsSelecting] = useState(false);

  const validateAndAddPoint = (x: number, y: number) => {
    if (!isSelecting) return;

    if (path.length === 0) {
      lastValidPoint.current = { x, y };
      setPath([{ x, y }]);
      return;
    }

    const lastPoint = lastValidPoint.current || path[path.length - 1];

    if (
      (Math.abs(lastPoint.x - x) === 1 && lastPoint.y === y) ||
      (Math.abs(lastPoint.y - y) === 1 && lastPoint.x === x)
    ) {
      if (!path.some((p) => p.x === x && p.y === y)) {
        lastValidPoint.current = { x, y };
        setPath((prev) => [...prev, { x, y }]);
      }
    }
  };

  const handleDotClick = (x: number, y: number) => {
    if (!isSelecting) {
      setPath([{ x, y }]);
      setIsSelecting(true);
      lastValidPoint.current = { x, y };
    } else {
      setIsSelecting(false);
      lastValidPoint.current = null;
    }
  };

  const handleMouseEnter = (x: number, y: number) => {
    if (isSelecting) {
      validateAndAddPoint(x, y);
    }
  };

  const startRobot = async () => {
    const instructions = convertPathToInstructions(path);

    fetch(`http://192.168.143.122/move?path=${instructions}`, {
      method: "GET",
      redirect: "follow",
    })
      .then((response) => response.text())
      .then((result) => console.log(result))
      .catch((error) => console.error(error));
  };

  const stopRobot = async () => {
    fetch("http://192.168.143.122/stop", {
      method: "GET",
      redirect: "follow",
    })
      .then((response) => response.text())
      .then((result) => console.log(result))
      .catch((error) => console.error(error));
  };

  const clearPath = () => {
    setPath([]);
    lastValidPoint.current = null;
    setIsSelecting(false);
  };

  return (
    <div className="flex flex-col gap-4 h-screen w-screen items-center justify-center">
      <div
        className="grid gap-1"
        style={{
          gridTemplateColumns: `repeat(${GRID_WIDTH}, ${CELL_SIZE}px)`,
          gridTemplateRows: `repeat(${GRID_HEIGHT}, ${CELL_SIZE}px)`,
        }}
      >
        {Array.from({ length: GRID_WIDTH * GRID_HEIGHT }).map((_, idx) => {
          const x = idx % GRID_WIDTH;
          const y = Math.floor(idx / GRID_WIDTH);

          const isSelected = path.some((p) => p.x === x && p.y === y);
          const isStart = path[0]?.x === x && path[0]?.y === y;
          const isEnd =
            path.length > 0 && path[path.length - 1]?.x === x && path[path.length - 1]?.y === y;

          return (
            <div
              key={idx}
              className={`
                w-10 h-10 rounded-md border transition-all duration-150
                ${isSelected ? "bg-blue-500 border-blue-600" : "bg-gray-100 border-gray-200"}
                ${isStart ? "bg-green-500 border-green-600" : ""}
                ${isEnd ? "bg-red-500 border-red-600" : ""}
                hover:border-blue-400 cursor-pointer
              `}
              onClick={() => handleDotClick(x, y)}
              onMouseEnter={() => handleMouseEnter(x, y)}
            />
          );
        })}
      </div>

      <div className=" bg-white shadow-2xl border-2 p-2 rounded-xl flex gap-4">
        <Button
          onClick={startRobot}
          disabled={path.length < 2}
          className="bg-green-500 hover:bg-green-600"
        >
          Start
        </Button>
        {/* <Button
          onClick={stopRobot}
          disabled={path.length < 2}
          className="bg-yellow-500 hover:bg-yellow-600"
        >
          Stop
        </Button> */}
        <Button onClick={clearPath} variant="destructive">
          Clear
        </Button>
      </div>
    </div>
  );
}
