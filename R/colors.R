#helper function to sample equally from color space
ggCol <- function(n) {
  hues = seq(15, 375, length = n + 1)
  hcl(h = hues, l = 65, c = 100)[1:n]
}

ggColOffset <- function(n,offset){
  hues = seq(15, 375, length = n + 1 + offset)
  hcl(h = hues,l = 65,c = 100)[(1+offset):(offset+n)]
}

#helper function to brighten or darken colors
colLuminosity <- function(color,factor,bright,alpha=NULL){

  if(!is.logical(bright)){ #sanity check
    stop("i don't know if you wan't me to make your color brighter or darker!")
  }

  col = col2rgb(color,alpha=FALSE) #convert to rgba color space
  if(bright){
    col = col*factor
  } else {
    col = col/factor
  }
  if(!is.null(alpha)){ #adjust alpha if specified
    rbind(col,alpha = 255 * alpha)
  }
  col = rgb(t(as.matrix(apply(col, 1, function(x) if (x > 255) 255 else x))), maxColorValue=255)
  return(col)
}
