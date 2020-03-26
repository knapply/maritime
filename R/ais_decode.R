#' Decode NMEA Messages
#' 
#' National Marine Electronics Association (NMEA) messages are comma separated value
#' lines of text that start with sender or "talker" code and the sentence type.
#' 
#' `ais_decode_nmea` decodes NMEA messages (currently 1, 2, and 3) contained in files or `character` vectors.
#' 
#' 
#' @param msgs `character()`
#'  * NMEA messages
#' @param data_type `character(1L)`
#' * how to interpret `x`.
#'   + one of `"auto"`, `"file"`, `"strings"`, or `"text"`
#'     + `"auto"`: let `ais_decode()` decide
#'     + `"file"`: treat `x` as a file path
#'     + `"strings"`: treat `x` as a vector with each element containing a single AIS message
#'     + `"text"`: treat `x` as a single `character` containing multiple AIS messages
#' @template param-as_df
#' @template param-as_sf
#' @template param-as_tibble
#' @template param-verbose
#' 
#' @template author-bk
#' 
#' @examples 
#' nmea_file <- example_nmea_file()
#' nmea_lines <- readLines(nmea_file, warn = FALSE)
#' 
#' nmea_lines[1:10]
#' 
#' # decoding a file =====================================================================
#' ais_decode_nmea(nmea_file)
#' 
#' @export
ais_decode_nmea <- function(msgs,
                            data_type = c("auto", "file", "strings", "text"),
                            as_df = maritime_as_df(),
                            as_sf = maritime_as_sf(),
                            as_tibble = maritime_as_tibble(),
                            verbose = maritime_verbose()) {
    data_type <- match.arg(data_type, c("auto", "file", "strings", "text"))
    
    if (!is.character(msgs) || anyNA(msgs)) {
        stop("`x` must be a be a character vector that doesn't contain `NA`.")
    }
    if (data_type == "auto") {
        if (all(file.exists(msgs))) {
            if (length(msgs) != 1L) {
                stop("Multiple files are not yet supported.")
            }
            data_type <- "file"
            msgs <- path.expand(msgs)
        } else if (length(msgs) > 2L) {
            data_type <- "strings"
        } else {
            data_type <- "text"
        }

        if (verbose) message(sprintf("- `data_type` detected: %s", data_type))
    }
    
    out <- switch(
        data_type,
        file = .ais_decode_file(msgs, as_df = as_df, verbose = verbose),
        strings = .ais_decode_strings(msgs, as_df = as_df, verbose = verbose),
        text =,
        stop("Not yet implemented.")
    )
    if (!as_df) return(out)
    
    if (as_tibble && requireNamespace("tibble", quietly = TRUE)) {
        out <- tibble::as_tibble(out)
    }
    
    if (as_sf && requireNamespace("sf", quietly = TRUE)) {
        out <- sf::st_as_sf(out, coords = c("lng_deg", "lat_deg"),
                            remove = FALSE,
                            crs = 4326L)
    }
    
    out
}


