/*
================================================================================

	gplaces - a simple terminal Gemini client
    Copyright (C) 2022 - 2024  Dima Krasner

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

================================================================================
*/
static void *finger_download(const Selector *sel, URL *url, char **mime, Parser *parser, unsigned int redirs, int ask) {
	static char buffer[1024 + 3]; /* path\r\n\0 */
	char *user = NULL;
	int fd = -1, len = 0;

	(void)sel;
	(void)redirs;
	(void)ask;

	switch (curl_url_get(url->cu, CURLUPART_USER, &user, 0)) {
	case CURLUE_OK: len = snprintf(buffer, sizeof(buffer), "%s\r\n", user); break;
	case CURLUE_NO_USER: break;
	default: return NULL;
	}

	if ((fd = socket_connect(url, SOCK_STREAM)) == -1) return NULL;
	if ((len == 0 && sendall(fd, "\r\n", 2, MSG_NOSIGNAL) != 2) || (len > 0 && sendall(fd, buffer, len, MSG_NOSIGNAL) != len)) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) error(0, "cannot send request to `%s`:`%s`: cancelled", url->host, url->port);
		else error(0, "cannot send request to `%s`:`%s`: %s", url->host, url->port, strerror(errno));
		close(fd);
		return NULL;
	}

	*mime = "text/plain";
	*parser = parse_plaintext_line;

	return (void *)(intptr_t)fd;
}


const Protocol finger = {"finger", "79", tcp_read, tcp_peek, socket_error, tcp_close, finger_download, set_fragment};
