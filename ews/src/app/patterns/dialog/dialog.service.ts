import { Injectable } from "@angular/core";
import { MatDialog, MatDialogConfig, MatDialogRef } from "@angular/material/dialog";
import { ComponentType } from '@angular/cdk/portal';

@Injectable({
    providedIn: 'root'
})
export class DialogService{
    constructor(private matDialog: MatDialog){}
    open(component:any, data?:any){
        let config = new MatDialogConfig();
        config.width = "1500px";
        config.maxHeight = "90vh";
        // config.closeOnNavigation = true;
        // disableClose: true
        config.data = data ?? {};
        return this.matDialog.open(component, config);
    }
}