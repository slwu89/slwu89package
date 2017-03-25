# perspCol: plot persp with color according to z-axis
# x: vector of x-axis points
# y: vector of y-axis points
# z: matrix of function evaluated on xy lattice
# color: vector of colors
# ...: additional parameters to be passed to persp()
# xlg: log x-axis
# ylg: log y-axis
perspCol <- function(x,y,z,color,xlg=TRUE,ylg=TRUE,ticktype="detailed",border=NA,...)
{
  colnames(z) <- y
  rownames(z) <- x

  nrz <- nrow(z)
  ncz <- ncol(z)

  nb.col = length(color)

  zfacet <- z[-1, -1] + z[-1, -ncz] + z[-nrz, -1] + z[-nrz, -ncz]
  facetcol <- cut(zfacet, nb.col)
  par(xlog=xlg,ylog=ylg)
  persp(
    as.numeric(rownames(z)),
    as.numeric(colnames(z)),
    as.matrix(z),
    col=color[facetcol],
    ticktype=ticktype,
    border=border,
    ...
  )
}

# makeSurface: generate xy lattice and apply function over lattice for perspective plot
# xlim: x-axis bounds
# ylim: y-axis bounds
# resolution: resolution of lattice
# func: function to apply to xy lattice
makeSurface <- function(xlim, ylim, resolution, func){
  xx = seq(xlim[1],xlim[2],length=resolution)
  yy = seq(ylim[1],ylim[2],length=resolution)
  zz = matrix(apply(expand.grid(xx,yy),1,func),nrow=length(xx))
  return(list(
    xx=xx,
    yy=yy,
    zz=zz
  ))
}
