/* From example.c in inotify-tools
 *
 * Copyright 2014 Laird
 * License: GPL v2, see COPYING
 */

#include <stdio.h>
#include <string.h>
#include <inotifytools/inotifytools.h>
#include <inotifytools/inotify.h>

#include "common.h"

#define EXCLUDE_CHUNK 1024
#define WR_EVENTS	(IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | \
			 IN_MOVED_FROM | \
			 IN_MOVED_TO | IN_DELETE | IN_CREATE | IN_DELETE_SELF | \
			 IN_MOVE_SELF)

/*
 * fs_watch - watch a file system
 *
 *  run: fs_watch @/dev @/tmp @/sys @/proc
 */
int main(int argc, char ** argv) {

	FileList list = construct_path_list( argc, argv, 0 );

	// initialize and watch the entire directory tree from the current working
	// directory downwards for all events
	if ( !inotifytools_initialize()
	  || !inotifytools_watch_recursively_with_exclude( "/", WR_EVENTS, list.exclude_files ) ) {
		fprintf(stderr, "%s\n", strerror( inotifytools_error() ) );
		return -1;
	}

	// set time format to 24 hour time, HH:MM:SS
	inotifytools_set_printf_timefmt( "%T" );

	// Output all events as "<timestamp> <path> <events>"
	struct inotify_event * event = inotifytools_next_event( -1 );
	while ( event ) {
		inotifytools_printf( event, "%T %w%f %e\n" );
		fflush(stdout);
		event = inotifytools_next_event( -1 );
	}
}
