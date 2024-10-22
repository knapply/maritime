#' Decode NMEA Messages
#'
#' National Marine Electronics Association (NMEA) messages are comma separated
#'  value lines of text that start with sender or "talker" code and the sentence
#'  type.
#'
#' `ais_decode_filter` decodes NMEA messages (currently 1, 2, and 3) contained
#' in files or `character` vectors.
#'
#'
#' @param msgs `character()`
#'  * NMEA messages
#' @param msg_type See `ais_msgs`
#' @param data_type `character(1L)`
#' * how to interpret `x`.
#'   + one of `"auto"`, `"file"`, `"strings"`, or `"text"`
#'     + `"auto"`: let `ais_decode()` decide
#'     + `"file"`: treat `x` as a file path
#'     + `"strings"`: treat `x` as a vector with each element containing a
#'        single AIS message
#'     + `"text"`: treat `x` as a single `character` containing multiple AIS
#'         messages
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
#' # decoding a file, filter by messgage type ==================================
#' ais_decode_filter(nmea_file, msg_type = ais_msgs$msg_1_2_3)
#'
#' # return all messages as list of data frames ================================
#' ais_decode_list(nmea_file)
#'
#' # return all messages, combined into a single data frame ====================
#' ais_decode_df(nmea_file)
#' @export
ais_decode_filter <- function(msgs,
                              msg_type = ais_msgs$msg_1_2_3,
                              data_type = c("auto", "file", "strings", "text"),
                              as_sf = maritime_as_sf(),
                              as_tibble = maritime_as_tibble(),
                              verbose = maritime_verbose()) {
  if (!inherits(msg_type, "ais_msg")) {
    stop("`msg_type` must be an `ais_msg`. See `ais_msgs`")
  }
  if (!is.character(msgs) || anyNA(msgs)) {
    stop("`msgs` must be a be a character vector that doesn't contain `NA`.")
  }

  data_type <- match.arg(data_type, c("auto", "file", "strings", "text"))

  if (data_type == "auto") {
    if (all(file.exists(msgs))) {
      if (length(msgs) != 1L) {
        stop("Multiple files are not yet supported.")
      }
      data_type <- "file"
      msgs <- path.expand(msgs)
    } else if (length(msgs) > 2L) {
      stop("`strings` are not yet supported.")
      data_type <- "strings"
    } else {
      stop("`text` is not yet supported.")
      data_type <- "text"
    }

    if (verbose) message(sprintf("- `data_type` detected: %s", data_type))
  }

  out <- switch(data_type,
    file = .ais_decode_filter_file(
      msgs,
      msg_type = msg_type, verbose = verbose
    ),
    strings = stop("Not yet implemented."),
    text = stop("Not yet implemented."),
    stop("Not yet implemented.")
  )

  if (as_tibble && requireNamespace("tibble", quietly = TRUE)) {
    out <- tibble::as_tibble(out)
  }

  if (as_sf && requireNamespace("sf", quietly = TRUE)) {
    warning("`as_sf` is not yet implemented.")
    out <- sf::st_as_sf(out,
      coords = c("lng_deg", "lat_deg"),
      remove = FALSE,
      crs = 4326L
    )
  }

  out
}


#' @rdname ais_decode_filter
#' @export
ais_decode_list <- function(msgs,
                            data_type = c("auto", "file", "strings", "text"),
                            as_sf = maritime_as_sf(),
                            as_tibble = maritime_as_tibble(),
                            verbose = maritime_verbose()) {
  if (!is.character(msgs) || anyNA(msgs)) {
    stop("`x` must be a be a character vector that doesn't contain `NA`.")
  }

  data_type <- match.arg(data_type, c("auto", "file", "strings", "text"))

  if (data_type == "auto") {
    if (all(file.exists(msgs))) {
      if (length(msgs) != 1L) {
        stop("Multiple files are not yet supported.")
      }
      data_type <- "file"
      msgs <- path.expand(msgs)
    } else if (length(msgs) > 2L) {
      stop("`strings` are not yet supported.")
      data_type <- "strings"
    } else {
      stop("`text` is not yet supported.")
      data_type <- "text"
    }

    if (verbose) message(sprintf("- `data_type` detected: %s", data_type))
  }

  out <- switch(data_type,
    file = .ais_decode_list_file(msgs, verbose = verbose),
    strings = stop("Not yet implemented."),
    text = stop("Not yet implemented."),
    stop("Not yet implemented.")
  )

  if (as_tibble && requireNamespace("tibble", quietly = TRUE)) {
    out <- lapply(out, tibble::as_tibble)
  }

  if (as_sf && requireNamespace("sf", quietly = TRUE)) {
    warning("`as_sf` is not yet implemented.")
    #     out <- sf::st_as_sf(out, coords = c("lng_deg", "lat_deg"),
    #                         remove = FALSE,
    #                         crs = 4326L)
  }

  out
}



#' @rdname ais_decode_filter
#' @param sort_by_line_number Whether rows are in the same order as line occurrence.
#'
#' @importFrom data.table rbindlist setkey
#' @export
ais_decode_df <- function(msgs,
                          data_type = c("auto", "file", "strings", "text"),
                          sort_by_line_number = TRUE,
                          as_sf = maritime_as_sf(),
                          as_tibble = maritime_as_tibble(),
                          verbose = maritime_verbose()) {
  if (!is.character(msgs) || anyNA(msgs)) {
    stop("`x` must be a be a character vector that doesn't contain `NA`.")
  }
  if (as_sf) {
    warning("`as_sf` is not yet implemented.")
  }

  data_type <- match.arg(data_type, c("auto", "file", "strings", "text"))

  if (data_type == "auto") {
    if (all(file.exists(msgs))) {
      if (length(msgs) != 1L) {
        stop("Multiple files are not yet supported.")
      }
      data_type <- "file"
      msgs <- path.expand(msgs)
    } else if (length(msgs) > 2L) {
      stop("`strings` are not yet supported.")
      data_type <- "strings"
    } else {
      stop("`text` is not yet supported.")
      data_type <- "text"
    }

    if (verbose) message(sprintf("- `data_type` detected: %s", data_type))
  }




  out <- switch(
    data_type,
    file = .ais_decode_list_file(msgs, verbose = verbose),

    strings = stop("Not yet implemented."),
    text = stop("Not yet implemented."),
    stop("Not yet implemented.")
  )

  out <- rbindlist(out, fill = TRUE, use.names = TRUE)

  if (sort_by_line_number) {
    setkey(out, first_line_number)
    out <- out[order(first_line_number)]
  }

  if (as_tibble && requireNamespace("tibble", quietly = TRUE)) {
    out <- tibble::as_tibble(out)
  }

  if (as_sf && requireNamespace("sf", quietly = TRUE)) {
    warning("`as_sf` is not yet implemented.")
    #     out <- sf::st_as_sf(out, coords = c("lng_deg", "lat_deg"),
    #                         remove = FALSE,
    #                         crs = 4326L)
  }

  out
}
