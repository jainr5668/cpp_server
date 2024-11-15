import { Component, OnInit, Input, Output, EventEmitter } from "@angular/core";
import { FormGroup } from "@angular/forms";
import { TranslateService } from "@ngx-translate/core";
import { clickListenerEvent } from "@patterns/common.model";
import { Observable } from "rxjs";
import { StringIdsType } from "src/stringIds";
import { ElementModel, ElementType } from './element.model';

@Component({
  selector: 'pattern-element',
  templateUrl: './element.component.html',
  styleUrls: ['./element.component.css'],
})
export class ElementComponent implements OnInit {
  @Input() public element: ElementModel;
  @Input() public formGroup: FormGroup;

  @Output() clickListener = new EventEmitter();
  elementType = ElementType;

  constructor(private translate: TranslateService) {
  }

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
  
  ngOnInit(): void {
    this.formGroup
      .get(this.element.id)
      .setValue(this.element.model[this.element.property]);
  }

  onClicked(event: any) {
    const eventObject = new clickListenerEvent(
      event,
      this.element.id,
      event.value
    );
    if (this.element.event) {
      this.element.event(eventObject);
    } else {
      this.clickListener.emit(eventObject);
    }
  }

  stateChange(event) {
    let value:any = '';
    switch (this.element.type) {
      case ElementType.SELECT:
        value = event.value;
        break;
      case ElementType.TEXT:
      case ElementType.PASSWORD:
        value = (event.target as HTMLInputElement).value;
        break;
      case ElementType.TOGGLE:
        value = event.checked;
        break
      case ElementType.FILE:
        const file = event.target.files[0];
        value = new FormData();
        value.append('file', file, file.name);
    }
    this.element.model[this.element.property] = this.formGroup.get(
      this.element.id
    ).value;
    if (this.element.type == ElementType.FILE) {
      this.element.model[this.element.property] = this.element.model[this.element.property].replace(/^.*\\/, "");
    }
    this.onClicked(value);
  }
}
