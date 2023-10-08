
        for (int j=0; j<i; j++){
            inssort2<E>(&A[j], n-j, i);
            for (int i =0; i<n;i++){
                cout << A[i] << " ";
            }
    }
            cout << endl;