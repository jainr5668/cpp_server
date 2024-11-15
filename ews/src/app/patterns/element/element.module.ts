import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { ElementComponent } from './element.component';
import { MatSelectModule } from '@angular/material/select';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInputModule } from '@angular/material/input';
import { MatSlideToggleModule } from '@angular/material/slide-toggle';
import { TranslateModule } from '@ngx-translate/core';
import { ButtonModule } from '@patterns/button';

@NgModule({
  declarations: [ElementComponent],
  imports: [
    CommonModule,
    MatSelectModule,
    FormsModule,
    ReactiveFormsModule,
    MatFormFieldModule,
    MatInputModule,
    MatSlideToggleModule,
    TranslateModule
  ],
  exports: [ElementComponent],
})
export class ElementModule {}