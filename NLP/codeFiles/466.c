#include &lt;windows.h&gt;#include &lt;stdio.h&gt;
#include &lt;wchar.h&gt;

int
main()
{
	FILETIME ft = {dwLowDateTime: 0, dwHighDateTime: 0};  /* Epoch */
	SYSTEMTIME st;
	wchar_t date[80], time[80];

	/*
	 * Convert FILETIME (which counts 100-nanosecond intervals since
	 * the epoch) to SYSTEMTIME (which has year, month, and so on).
	 *
	 * The time is in UTC, because we never call
	 * SystemTimeToTzSpecificLocalTime() to convert it to local time.
	 */
	FileTimeToSystemTime(&amp;ft, &amp;st);

	/*
	 * Format SYSTEMTIME as a string.
	 */
	if (GetDateFormatW(LOCALE_USER_DEFAULT, DATE_LONGDATE, &amp;st, NULL,
	    date, sizeof date / sizeof date[0]) == 0 ||
	    GetTimeFormatW(LOCALE_USER_DEFAULT, 0, &amp;st, NULL,
	    time, sizeof time / sizeof time[0]) == 0) {
		fwprintf(stderr, L&quot;Error!\n&quot;);
		return 1;
	}

	wprintf(L&quot;FileTime epoch is %ls, at %ls (UTC).\n&quot;, date, time);
	return 0;
}
