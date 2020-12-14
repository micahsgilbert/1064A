const resizeCoverOverlay = () => {
  document.getElementById("gradient-cover").style.height = Math.min(window.innerHeight, 0.6434 * window.innerWidth) + "px"
}

window.addEventListener("load", resizeCoverOverlay)
window.addEventListener("resize", resizeCoverOverlay)