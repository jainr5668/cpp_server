import { ComponentType } from "@angular/cdk/portal";
import { Type } from "@angular/core";
import { MatDialogConfig } from "@angular/material/dialog";
import { Subject } from "rxjs";

export class DialogModel{
    component:ComponentType<unknown>;
    config:MatDialogConfig;
};

export class DialogConfigData{
    /**
     * Optional data to pass to the content component
     */
    contentComponentData: any = null;
    /**
     * Optional data to pass to the content component, representing the state of the content component
     * Handy to be used in order to display the result of an operation in the dialog.
     */
    stateFromParent: any = null;
    /**
     * Optional event emitted by content component
     */
    contentComponentEvent: Subject<any>;
}