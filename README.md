# TP_FSM

## Abstract

The tool is composed of two parts : 
The Indexing Server : a service running in the background which listens on port 7007 TCP (configurable).
The indexing client : which communicates with the server to set it up, get informations on the index and make requests
The connection between the client & the server is continuous

## The server 
On start, the service scans the StartFolder (usually a configurable drive) and builds a database with all the found files.

## The client
Thanks to a specific dialect the client can get information, set up the server and make queries.

## Key Concept
WHITELIST : prefered folder, should be indexed fist and more often
BLACKLIST : never index these folders
SKIPPED FILTERS : extensions to never index
FILTERS : index only these extensions

## The Dialect
# Common
the dialect is case insensitive
the dialect is full ASCII, the UTF8 characters are percent-encoded (url-encoded)

# Server side
STATUS
When its status change the server send to the client the word status followed by the current status

e.g. STATUS INDEXING

TABLE OF SERVER STATUSES
status
description
INDEXING
full indexation in progress
READY
indexation done
STOPPED
client stopped the indexing
PAUSED
client paused the indexing
QUERYING
a query is in progress
RESULTS_AVAILABLE
the query is finished and some results are waiting

# Client Side
Indexer State & setup
INDEXER <STATUS|START|STOP|PAUSE|RESUME>
Get status and Controls the indexing
GET <WHITELIST|BLACKLIST|FILTERS|SKIPPED_FILTERS>
ADD <WHITELIST|BLACKLIST|FILTERS|SKIPPED_FILTERS> <folder to add>
PUSH <WHITELIST|BLACKLIST|FILTERS|SKIPPED_FILTERS>  <folders to add>  DONE

Example :
PUSH WHITELIST
C:/
d:/
DONE

CLEAR <WHITELIST|BLACKLIST|FILTERS|SKIPPED_FILTERS>
Querying
SEARCH <filename_part> [OPTIONS]
Options
LAST_MODIFIED: <date_spec>
CREATED: <date_spec>
MAX_SIZE:<size_spec>
MIN_SIZE: <size_spec>
SIZE: <size_spec|size_spec_ex>
EXT:<list_of_extensions>
TYPE: <type_list_spec>
date_spec : 
dd/mm/yyyy
mm/yyyy
yyyy
yy
SINCE LAST <number> <MINUTES|HOURS|DAYS|MONTHS|YEAR>
<number> <MINUTES|HOURS|DAYS|MONTHS|YEAR> AGO
BETWEEN <date_spec> AND <date_spec>
size_spec:
<number><K|M|G>
size_spec_ex : 
BETWEEN <size_spec> AND <size_spec>
ext_list_spec : 
<ext>, <ext>, ….
<ext> OR <ext> OR ….

type_list_spec : 
<type>, <type>, ….
<type> OR <type> OR ….
type:
image : jpg,png,gif, ….
text: txt, html,.....
exe: exe, bat, sh
Example

SEARCH "testme please" 
LAST_MODIFIED:BETWEEN 2 days and 3 days 
CREATED:31/12/2020 
MAX_SIZE:10M 
MIN_SIZE:1M 
SIZE:BETWEEN 10M AND 20M 
EXT:txt,doc,xlsx 
TYPE:image OR text