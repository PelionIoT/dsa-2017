# DSA 2017 - Fieldwork results (dairy farm)

**cow_data_xyz_time_resampled.csv**

This is data from the accelerometer.

Fields are:

* x – x axis of sensor (int)
* y – y axis of sensor (int)
* z – z axis of sensor (int)
* time – original timestamp (`datetime string python date_format='%Y-%m-%dT%H:%M:%S.%f'`)
* time_resampled – timestamp resampled so that timestamps are an increasing sequence. Assumes that each sample was gathered 30ms after previous (original json was a hard to interpret in a field with a crowd watching (see picture)). (`datetime string python date_format='%Y-%m-%dT%H:%M:%S.%f'`)

**tagged_cow_data.csv**

This is the hand-tagged data.

Symbols are:

* `r` = run
* `s` = stop
* `w` = walk
* `m` = moo
* `i` = itch
* `e` = eat
* `f` = fight
