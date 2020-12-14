const resizeCoverOverlay = () => {
  document.getElementById("gradient-cover").style.height = Math.min(document.getElementById("cover").height, window.innerHeight) + "px"
}

window.addEventListener("load", resizeCoverOverlay)
window.addEventListener('resize', resizeCoverOverlay)