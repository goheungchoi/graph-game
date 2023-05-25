export function drawLine(ctx, begin, end, stroke='black', width=1) {
  if (stroke) {
    ctx.strokeStyle = stroke;
  }

  if (width) {
      ctx.lineWidth = width;
  }

  ctx.beginPath();
  ctx.moveTo(...begin);
  ctx.lineTo(...end);
  ctx.stroke();
}

export function drawCircle(
  ctx, center, rad, 
  color="gray", stroke='black', width=1) 
{
  if (color) {
    ctx.fillStyle = color;
  }
  
  if (stroke) {
    ctx.strokeStyle = stroke;
  }

  if (width) {
    ctx.lineWidth = width;
  }

  ctx.beginPath();
  ctx.arc(center[0], center[1], rad, 0, 2*Math.PI);
  ctx.stroke();
  ctx.fill();
}