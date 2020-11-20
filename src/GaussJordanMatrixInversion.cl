__kernel fixRow(int *matrix, int size, int rowId)
{
    __local float Ri[512];
    __local float Aii;
    
    int colId = get_local_id(0);
    
    Ri[colId] = matrix[size * rowId + colId];
    Aii = matrix[size * rowId + sharedRowId];
    
    barrier();
    
    Ri[colId] = Ri[colId]/Aii;
    matrix[size * rowId + colId] = Ri[colId];
}
