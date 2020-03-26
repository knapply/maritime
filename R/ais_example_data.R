#' Path to Example File
#' 
#' Path to a file containing example NMEA messages. 
#' 
#' @return `character(1L)` file path
#' 
#' @template author-cc
#' 
#' @examples 
#' example_nmea_file()
#' 
#' @export
example_nmea_file <- function() {
    system.file("example-data/20181101.log", package = "maritime")
}