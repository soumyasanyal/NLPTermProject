#include &lt;stdio.h&gt;
int main()
{
        int i, j;
        double degrees[] = { 0.0, 16.87, 16.88, 33.75, 50.62, 50.63, 67.5,
                84.37, 84.38, 101.25, 118.12, 118.13, 135.0, 151.87, 151.88,
                168.75, 185.62, 185.63, 202.5, 219.37, 219.38, 236.25, 253.12,
                253.13, 270.0, 286.87, 286.88, 303.75, 320.62, 320.63, 337.5,
                354.37, 354.38 };
        char * names =  &quot;North                 &quot;
                        &quot;North by east         &quot;
                        &quot;North-northeast       &quot;
                        &quot;Northeast by north    &quot;
                        &quot;Northeast             &quot;
                        &quot;Northeast by east     &quot;
                        &quot;East-northeast        &quot;
                        &quot;East by north         &quot;
                        &quot;East                  &quot;
                        &quot;East by south         &quot;
                        &quot;East-southeast        &quot;
                        &quot;Southeast by east     &quot;
                        &quot;Southeast             &quot;
                        &quot;Southeast by south    &quot;
                        &quot;South-southeast       &quot;
                        &quot;South by east         &quot;
                        &quot;South                 &quot;
                        &quot;South by west         &quot;
                        &quot;South-southwest       &quot;
                        &quot;Southwest by south    &quot;
                        &quot;Southwest             &quot;
                        &quot;Southwest by west     &quot;
                        &quot;West-southwest        &quot;
                        &quot;West by south         &quot;
                        &quot;West                  &quot;
                        &quot;West by north         &quot;
                        &quot;West-northwest        &quot;
                        &quot;Northwest by west     &quot;
                        &quot;Northwest             &quot;
                        &quot;Northwest by north    &quot;
                        &quot;North-northwest       &quot;
                        &quot;North by west         &quot;
                        &quot;North                 &quot;;

        for (i = 0; i &lt; 33; i++) {
                j = .5 + degrees[i] * 32 / 360;

                printf(&quot;%2d  %.22s  %6.2f\n&quot;, (j % 32) + 1, names + (j % 32) * 22,
                        degrees[i]);
        }

        return 0;
}
