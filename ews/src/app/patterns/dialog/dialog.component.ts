import { Component, OnInit, Input, Output, EventEmitter } from "@angular/core";
import { FormControl, FormGroup } from "@angular/forms";
import { TranslateService } from "@ngx-translate/core";
import { clickListenerEvent } from "@patterns/common.model";
import { Observable, map } from "rxjs";
import { StringIds, StringIdsType } from "src/stringIds";
import { DialogModel } from "./dialog.model";
import { STRING_TYPE } from "@angular/compiler";
import { MatDialog } from "@angular/material/dialog";

@Component({
  selector: 'pattern-dialog',
  templateUrl: './dialog.component.html',
  styleUrls: ['./dialog.component.css'],
})
export class DialogComponent implements OnInit {
  @Input() public dialog: DialogModel;

  @Output() clickListener = new EventEmitter();
  constructor(private translate: TranslateService, public matDialog: MatDialog) {}
  ngOnInit(): void {
    
  }
}