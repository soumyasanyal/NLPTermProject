#include &lt;stdio.h&gt;#define TALLOC(n,typ) malloc(n*sizeof(typ))

#define EL_Type int

typedef struct sMtx {
    int     dim_x, dim_y;
    EL_Type *m_stor;
    EL_Type **mtx;
} *Matrix, sMatrix;

typedef struct sRvec {
    int     dim_x;
    EL_Type *m_stor;
} *RowVec, sRowVec;

Matrix NewMatrix( int x_dim, int y_dim )
{
    int n;
    Matrix m;
    m = TALLOC( 1, sMatrix);
    n = x_dim * y_dim;
    m-&gt;dim_x = x_dim;
    m-&gt;dim_y = y_dim;
    m-&gt;m_stor = TALLOC(n, EL_Type);
    m-&gt;mtx = TALLOC(m-&gt;dim_y, EL_Type *);
    for(n=0; n&lt;y_dim; n++) {
        m-&gt;mtx[n] = m-&gt;m_stor+n*x_dim;
    }
    return m;
}

void MtxSetRow(Matrix m, int irow, EL_Type *v)
{
    int ix;
    EL_Type *mr;
    mr = m-&gt;mtx[irow];
    for(ix=0; ix&lt;m-&gt;dim_x; ix++)
        mr[ix] = v[ix];
}

Matrix InitMatrix( int x_dim, int y_dim, EL_Type **v)
{
    Matrix m;
    int iy;
    m = NewMatrix(x_dim, y_dim);
    for (iy=0; iy&lt;y_dim; iy++) 
        MtxSetRow(m, iy, v[iy]);
    return m;
}

void MtxDisplay( Matrix m )
{
    int iy, ix;
    const char *sc;
    for (iy=0; iy&lt;m-&gt;dim_y; iy++) {
        printf(&quot;   &quot;);
        sc = &quot; &quot;;
        for (ix=0; ix&lt;m-&gt;dim_x; ix++) {
            printf(&quot;%s %3d&quot;, sc, m-&gt;mtx[iy][ix]);
            sc = &quot;,&quot;;
        }
        printf(&quot;\n&quot;);
    }
    printf(&quot;\n&quot;);
}

void MtxMulAndAddRows(Matrix m, int ixrdest, int ixrsrc, EL_Type mplr)
{
    int ix;
    EL_Type *drow, *srow;
    drow = m-&gt;mtx[ixrdest];
    srow = m-&gt;mtx[ixrsrc];
    for (ix=0; ix&lt;m-&gt;dim_x; ix++) 
        drow[ix] += mplr * srow[ix];
//	printf(&quot;Mul row %d by %d and add to row %d\n&quot;, ixrsrc, mplr, ixrdest);
//	MtxDisplay(m);
}

void MtxSwapRows( Matrix m, int rix1, int rix2)
{
    EL_Type *r1, *r2, temp;
    int ix;
    if (rix1 == rix2) return;
    r1 = m-&gt;mtx[rix1];
    r2 = m-&gt;mtx[rix2];
    for (ix=0; ix&lt;m-&gt;dim_x; ix++)
        temp = r1[ix]; r1[ix]=r2[ix]; r2[ix]=temp;
//	printf(&quot;Swap rows %d and %d\n&quot;, rix1, rix2);
//	MtxDisplay(m);
}

void MtxNormalizeRow( Matrix m, int rix, int lead)
{
    int ix;
    EL_Type *drow;
    EL_Type lv;
    drow = m-&gt;mtx[rix];
    lv = drow[lead];
    for (ix=0; ix&lt;m-&gt;dim_x; ix++)
        drow[ix] /= lv;
//	printf(&quot;Normalize row %d\n&quot;, rix);
//	MtxDisplay(m);
}

#define MtxGet( m, rix, cix ) m-&gt;mtx[rix][cix]

void MtxToReducedREForm(Matrix m)
{
    int lead;
    int rix, iix;
    EL_Type lv;
    int rowCount = m-&gt;dim_y;

    lead = 0;
    for (rix=0; rix&lt;rowCount; rix++) {
        if (lead &gt;= m-&gt;dim_x)
            return;
        iix = rix;
        while (0 == MtxGet(m, iix,lead)) {
            iix++;
            if (iix == rowCount) {
                iix = rix;
                lead++;
                if (lead == m-&gt;dim_x)
                    return;
            }
        }
        MtxSwapRows(m, iix, rix );
        MtxNormalizeRow(m, rix, lead );
        for (iix=0; iix&lt;rowCount; iix++) {
            if ( iix != rix ) {
                lv = MtxGet(m, iix, lead );
                MtxMulAndAddRows(m,iix, rix, -lv) ;
            }
        }
        lead++;
    }
}

int main()
{
    Matrix m1;
    static EL_Type r1[] = {1,2,-1,-4};
    static EL_Type r2[] = {2,3,-1,-11};
    static EL_Type r3[] = {-2,0,-3,22};
    static EL_Type *im[] = { r1, r2, r3 };

    m1 = InitMatrix( 4,3, im );
    printf(&quot;Initial\n&quot;);
    MtxDisplay(m1);
    MtxToReducedREForm(m1);
    printf(&quot;Reduced R-E form\n&quot;);
    MtxDisplay(m1);
    return 0;
}
